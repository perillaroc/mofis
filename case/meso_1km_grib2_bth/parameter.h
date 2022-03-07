#pragma once
#include <string>


namespace mofis {
struct Parameter {
    std::string short_name;
    int discipline = -1;
    int parameter_category = -1;
    int parameter_number = -1;
};
}

