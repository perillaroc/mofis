#pragma once
#include <optional>
#include <eccodes.h>

#include "query.h"


namespace mofis {
struct LevelType {
    std::optional<std::string> name;
    KeyDict keys;

    bool check(codes_handle* handler) const;
};
}
