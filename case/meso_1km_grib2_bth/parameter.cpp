//
// Created by wangdp on 2022/3/7.
//

#include "parameter.h"
#include "grib_util.h"


bool mofis::Parameter::check(codes_handle* handler) const {
    if(!short_name.empty()) {
        auto message_short_name = mofis::getString(handler, "shortName");
        if(message_short_name == short_name) {
            return true;
        } else {
            return false;
        }
    }

    if(discipline != -1 && parameter_category != -1 && parameter_number != -1) {
        auto message_discipline = mofis::getLong(handler, "discipline");
        auto message_parameter_category = mofis::getLong(handler, "parameterCategory");
        auto message_parameter_number = mofis::getLong(handler, "parameterNumber");

        return discipline == message_discipline && parameter_category == message_parameter_category && parameter_number == message_parameter_number;
    }

    return true;
}
