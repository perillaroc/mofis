#include "level.h"
#include "grib_util.h"


bool mofis::Level::check(codes_handle *handler) const {
    if(value.has_value()) {
        auto message_level = mofis::getDouble(handler, "level");
        return message_level == this->value.value();
    }

    return checkKeys(handler, keys);
}
