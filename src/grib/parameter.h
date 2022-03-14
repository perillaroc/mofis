#pragma once
#include <string>
#include <optional>

#include <eccodes.h>

#include "query.h"


namespace mofis {
struct Parameter {
    std::optional<std::string> short_name;
    KeyDict keys;

    Parameter() = default;
    Parameter(const std::string &short_name);
    Parameter(const KeyDict &values);

    bool check(codes_handle* handler) const;
};
}

