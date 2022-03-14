#include <iostream>
#include <vector>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include <message.h>

using namespace fmt::literals;

std::string get_file_path(int forecast_hour) {
    auto file_template = "/g2/nwp_sp/OPER_ARCHIVE/GRAPES_MESO_1KM/Prod-grib/2022030700/ORIG/rmf.hgra.2022030700{:03}.grb2";
    return fmt::format(file_template, forecast_hour);
}

struct QueryParams {
    mofis::Parameter parameter;
    mofis::LevelType level_type;
    mofis::Level level;
};


int main() {
    std::vector<QueryParams> production_list = {
        {{{{"discipline", 0}, {"parameterCategory", 3}, {"parameterNumber", 5}}},{}, {}},
        {{"2t"}, {}, {}},
        {{"2r"}, {}, {}},
        {{"10u"}, {}, {}},
        {{"10v"}, {}, {}},
        {{{{"discipline", 0}, {"parameterCategory", 2}, {"parameterNumber", 22}}},{}, {10}},
        {{{{"discipline", 0}, {"parameterCategory", 1}, {"parameterNumber", 3}}},{}, {}},
        {{{{"discipline", 0}, {"parameterCategory", 19}, {"parameterNumber", 0}}},{}, {}},
        {{{{"discipline", 0}, {"parameterCategory", 3}, {"parameterNumber", 0}}},{}, {}},
        {{"t"}, {"surface"}, {}},
        {{{{"discipline", 0}, {"parameterCategory", 6}, {"parameterNumber", 1}}},{}, {}},
        {{{{"discipline", 0}, {"parameterCategory", 6}, {"parameterNumber", 3}}},{}, {}},
        {{{{"discipline", 0}, {"parameterCategory", 1}, {"parameterNumber", 8}}},{}, {}},
        {{{{"discipline", 0}, {"parameterCategory", 1}, {"parameterNumber", 29}}},{}, {}},
        {{"2d"}, {}, {}},
        {{{{"discipline", 0}, {"parameterCategory", 3}, {"parameterNumber", 225}}},{"surface"}, {}},
        {{{{"discipline", 0}, {"parameterCategory", 16}, {"parameterNumber", 224}}},{"surface"}, {}},
        {{{{"discipline", 0}, {"parameterCategory", 1}, {"parameterNumber", 19}}},{}, {}},

        {{"t"}, {"isobaricInhPa"}, {925}},
        {{"t"}, {"isobaricInhPa"}, {850}},
        {{"t"}, {"isobaricInhPa"}, {800}},
        {{"t"}, {"isobaricInhPa"}, {700}},
        {{"t"}, {"isobaricInhPa"}, {500}},

        {{"q"}, {"isobaricInhPa"}, {925}},
        {{"q"}, {"isobaricInhPa"}, {850}},
        {{"q"}, {"isobaricInhPa"}, {800}},
        {{"q"}, {"isobaricInhPa"}, {700}},
        {{"q"}, {"isobaricInhPa"}, {500}},

        {{"gh"}, {"isobaricInhPa"}, {925}},
        {{"gh"}, {"isobaricInhPa"}, {850}},
        {{"gh"}, {"isobaricInhPa"}, {800}},
        {{"gh"}, {"isobaricInhPa"}, {700}},
        {{"gh"}, {"isobaricInhPa"}, {500}},

        {{"u"}, {"isobaricInhPa"}, {925}},
        {{"u"}, {"isobaricInhPa"}, {850}},
        {{"u"}, {"isobaricInhPa"}, {800}},
        {{"u"}, {"isobaricInhPa"}, {700}},
        {{"u"}, {"isobaricInhPa"}, {500}},

        {{"v"}, {"isobaricInhPa"}, {925}},
        {{"v"}, {"isobaricInhPa"}, {850}},
        {{"v"}, {"isobaricInhPa"}, {800}},
        {{"v"}, {"isobaricInhPa"}, {700}},
        {{"v"}, {"isobaricInhPa"}, {500}},

        {{"wz"}, {"isobaricInhPa"}, {925}},
        {{"wz"}, {"isobaricInhPa"}, {850}},
        {{"wz"}, {"isobaricInhPa"}, {800}},
        {{"wz"}, {"isobaricInhPa"}, {700}},
        {{"wz"}, {"isobaricInhPa"}, {500}},

        {{"r"}, {"isobaricInhPa"}, {925}},
        {{"r"}, {"isobaricInhPa"}, {850}},
        {{"r"}, {"isobaricInhPa"}, {800}},
        {{"r"}, {"isobaricInhPa"}, {700}},
        {{"r"}, {"isobaricInhPa"}, {500}},
    };

    auto file_path = get_file_path(2);
    fmt::print("file path: {file_path}\n", "file_path"_a=file_path);

    auto count = -1;
    for(const auto& query: production_list) {
        count ++;
        auto parameter = query.parameter;
        auto level_type = query.level_type;
        auto level = query.level;

        auto handler = meso_1km_post::load_message_from_file(file_path, parameter, level_type, level);

        if(handler == nullptr) {
            fmt::print(std::cerr, "message not found: {}\n", count);
            continue;
        }

        fmt::print("get discipline...\n");
        long discipline = -1;
        auto err = codes_get_long(handler, "discipline", &discipline);
        if (err != 0) {
            fmt::print(std::cerr, "codes_get_long has error: {}\n", err);
        }
        fmt::print("discipline: {discipline}\n", "discipline"_a = discipline);

        codes_handle_delete(handler);
    }

    return 0;
}
