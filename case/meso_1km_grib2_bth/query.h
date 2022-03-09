#pragma once
#include <variant>
#include <map>
#include <string>


namespace mofis {
using ValueType = std::variant<long, double, std::string>;
using KeyNameType = std::string;
using KeyDict = std::map<KeyNameType , ValueType>;
}