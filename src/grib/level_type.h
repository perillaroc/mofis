#pragma once
#include <optional>
#include <eccodes.h>

#include "query.h"


namespace mofis {
struct LevelType {
    std::optional<std::string> name;
    KeyDict keys;

    LevelType() = default;
    LevelType(const std::string &value);
    LevelType(const KeyDict &values);

    bool check(codes_handle* handler) const;
};
}
