//
// Created by wangdp on 2022/3/7.
//

#include "parameter.h"
#include "grib_util.h"


bool mofis::Parameter::check(codes_handle* handler) const {
    if(short_name.has_value()) {
        auto message_short_name = mofis::getString(handler, "shortName");
        if(message_short_name == short_name.value()) {
            return true;
        } else {
            return false;
        }
    }

    return checkKeys(handler, keys);
}

mofis::Parameter::Parameter(const mofis::KeyDict &values) {
    keys = values;
}

mofis::Parameter::Parameter(const std::string &short_name): short_name(short_name) {

}
