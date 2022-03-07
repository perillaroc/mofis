#pragma once

#include <eccodes.h>
#include <string>

#include "parameter.h"
#include "level_type.h"
#include "level.h"

namespace meso_1km_post {
codes_handle* load_message_from_file(
        const std::string& file_path,
        const mofis::Parameter& parameter,
        const mofis::LevelType& level_type,
        const mofis::Level& level
);
}