#pragma once
#include <string>
#include <optional>

#include <eccodes.h>

#include "query.h"


namespace mofis {
struct Parameter {
    std::optional<std::string> short_name;
    KeyDict keys;

    bool check(codes_handle* handler) const;
};
}

