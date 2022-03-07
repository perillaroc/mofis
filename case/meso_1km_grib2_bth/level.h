#pragma once
#include <string>
#include <map>


namespace mofis {
struct Level {
    double value;
    std::map<std::string, std::string> keys;
};
}
