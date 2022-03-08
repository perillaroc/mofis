#pragma once
#include <string>

#include <eccodes.h>


namespace mofis {
struct Parameter {
    std::string short_name;
    int discipline = -1;
    int parameter_category = -1;
    int parameter_number = -1;

    bool check(codes_handle* handler) const;
};
}

