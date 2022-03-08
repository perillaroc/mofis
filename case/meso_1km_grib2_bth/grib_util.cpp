#include "grib_util.h"

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
