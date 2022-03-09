#pragma once

#include <eccodes.h>

#include "query.h"


namespace mofis {

std::string getString(codes_handle* handler, const std::string& key);

double getDouble(codes_handle* handler, const std::string& key);

long getLong(codes_handle* handler, const std::string& key);

bool checkValue(codes_handle* handler, const KeyNameType& key_name, const ValueType& value);

bool checkKeys(codes_handle* handler, const KeyDict& keys);

}
