#pragma once
#include <eccodes.h>
#include <optional>

#include "query.h"


namespace mofis {
struct Level {
    std::optional<double> value;
    KeyDict keys;

    Level() = default;
    Level(const KeyDict &keys);
    Level(double value);

    bool check(codes_handle* handler) const;
};
}
