#include "grib_util.h"

#include <stdexcept>


std::string mofis::getString(codes_handle *handler, const std::string &key) {
    char values[10240];
    size_t len = sizeof(values);

    values[0] = 0;

    CODES_CHECK(codes_get_string(handler, key.c_str(), values, &len), nullptr);
    // ASSERT(err)

    return values;
}

double mofis::getDouble(codes_handle *handler, const std::string &key) {
    double v = 0;
    CODES_CHECK(codes_get_double(handler, key.c_str(), &v), nullptr);
    return v;
}

long mofis::getLong(codes_handle *handler, const std::string &key) {
    long v = 0;
    CODES_CHECK(codes_get_long(handler, key.c_str(), &v), nullptr);
    return v;
}


bool mofis::checkValue(codes_handle *handler, const mofis::KeyNameType &key_name, const mofis::ValueType& value) {
    if(std::holds_alternative<long>(value)) {
        auto v = mofis::getLong(handler, key_name);
        return v == std::get<long>(value);
    } else if(std::holds_alternative<double>(value)) {
        auto v = mofis::getDouble(handler, key_name);
        return v == std::get<double>(value);
    } else if(std::holds_alternative<std::string>(value)) {
        auto v = mofis::getString(handler, key_name);
        return v == std::get<std::string>(value);
    } else {
        throw std::logic_error("key value type is not supported.");
    }
    return false;
}

bool mofis::checkKeys(codes_handle *handler, const mofis::KeyDict &keys) {
    for(const auto & key : keys) {
        auto key_name = key.first;
        auto key_value = key.second;
        if(!checkValue(handler, key_name, key_value)) {
            return false;
        }
    }
    return true;
}

