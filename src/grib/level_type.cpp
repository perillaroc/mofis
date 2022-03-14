#include "level_type.h"

#include "grib_util.h"

bool mofis::LevelType::check(codes_handle *handler) const {
    if(this->name.has_value()) {
        auto message_level_type = mofis::getString(handler, "typeOfLevel");
        return message_level_type == this->name.value();
    }

    return checkKeys(handler, keys);
}

mofis::LevelType::LevelType(const std::string &value): name(value) {

}

mofis::LevelType::LevelType(const mofis::KeyDict &values) {
    keys = values;
}
