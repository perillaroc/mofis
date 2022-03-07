#include <cstdio>
#include <iostream>

#include "message.h"

using namespace meso_1km_post;


std::string getString(codes_handle* handler, const std::string& key) {
    char values[10240];
    size_t len = sizeof(values);

    values[0] = 0;

    CODES_CHECK(codes_get_string(handler, key.c_str(), values, &len), nullptr);
    // ASSERT(err)

    return values;
}

double getDouble(codes_handle* handler, const std::string& key) {
    double v = 0;
    CODES_CHECK(codes_get_double(handler, key.c_str(), &v), nullptr);
    return v;
}

long getLong(codes_handle* handler, const std::string& key) {
    long v = 0;
    CODES_CHECK(codes_get_long(handler, key.c_str(), &v), nullptr);
    return v;
}


codes_handle* meso_1km_post::load_message_from_file(
        const std::string& file_path,
        const mofis::Parameter& parameter,
        const mofis::LevelType& level_type,
        const mofis::Level& level
){
    auto grib_file = std::fopen(file_path.c_str(), "r");
    if(grib_file == nullptr){
        std::cerr << "Unable to open file " << file_path << std::endl;
        return nullptr;
    }

    int err = 0;
    codes_handle* handler = nullptr;
//    std::cout << "create handler..." << std::endl;

    while((handler = codes_handle_new_from_file(nullptr, grib_file, PRODUCT_GRIB, &err)) != nullptr){
        if (err != CODES_SUCCESS) {
            std::cerr << "codes_handle_new_from_file has an error:" << err <<std::endl;
            std::fclose(grib_file);
            break;
        }

        auto count = getLong(handler, "count");
//        std::cout<<"message "<<count<<" ..."<<std::endl;

        auto message_short_name = getString(handler, "shortName");
        if(message_short_name != parameter.short_name) {
//            std::cout<<"short_name "<<message_short_name<<" != "<<parameter.short_name<<std::endl;
            codes_handle_delete(handler);
            continue;
        }

        auto message_level_type = getString(handler, "typeOfLevel");
        if(message_level_type != level_type.name) {
//            std::cout<<"level_type "<<message_level_type<<" != "<<level_type.name<<std::endl;
            codes_handle_delete(handler);
            continue;
        }

        auto message_level = getDouble(handler, "level");
        if(message_level != level.value){
//            std::cout<<"level "<<message_level<<" != "<<level.value<<std::endl;
            codes_handle_delete(handler);
            continue;
        }

        auto new_handler = codes_handle_clone(handler);
        codes_handle_delete(handler);
        handler = new_handler;
        break;
    }

    std::fclose(grib_file);
    return handler;
}
