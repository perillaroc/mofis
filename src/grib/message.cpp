#include <cstdio>
#include <iostream>

#include <fmt/format.h>

#include "message.h"
#include "grib_util.h"

using namespace meso_1km_post;


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

        auto count = mofis::getLong(handler, "count");
//        fmt::print("check message {}...", count);

        if(!parameter.check(handler)) {
            codes_handle_delete(handler);
//            fmt::print("failed\n");
            continue;
        }

        if(!level_type.check(handler)) {
            codes_handle_delete(handler);
//            fmt::print("failed\n");
            continue;
        }

        if(!level.check(handler)){
            codes_handle_delete(handler);
//            fmt::print("failed\n");
            continue;
        }

        auto new_handler = codes_handle_clone(handler);
        codes_handle_delete(handler);
        handler = new_handler;
//        fmt::print("success\n");
        break;
    }

    std::fclose(grib_file);
    return handler;
}
