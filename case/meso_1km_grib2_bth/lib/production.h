#pragma once
#include <string>
#include <vector>

#include <message.h>


namespace grib2_bth {

std::string get_file_path(int forecast_hour);


struct QueryParams {
    mofis::Parameter parameter;
    mofis::LevelType level_type;
    mofis::Level level;
    std::string name;
};


std::vector<QueryParams> get_production_list();
}
