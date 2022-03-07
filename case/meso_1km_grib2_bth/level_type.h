#pragma once
#include <string>
#include <map>


namespace mofis {
struct LevelType {
    std::string name;
    std::map<std::string, std::string> keys;
};
}
