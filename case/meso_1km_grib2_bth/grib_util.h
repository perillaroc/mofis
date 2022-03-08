#pragma once

#include <string>

#include <eccodes.h>


namespace mofis {

std::string getString(codes_handle* handler, const std::string& key);

double getDouble(codes_handle* handler, const std::string& key);

long getLong(codes_handle* handler, const std::string& key);

}
