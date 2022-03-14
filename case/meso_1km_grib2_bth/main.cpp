#include <iostream>
#include <vector>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include <message.h>

using namespace fmt::literals;

std::string get_file_path(int forecast_hour) {
//    auto file_template = "/g2/nwp_sp/OPER_ARCHIVE/GRAPES_MESO_1KM/Prod-grib/2022030700/ORIG/rmf.hgra.2022030700{:03}.grb2";
    auto file_template = "/g11/wangdp/project/work/data/playground/winter/grid-bth/data/2022030700/ORIG/rmf.hgra.2022030700{:03}.grb2";
    return fmt::format(file_template, forecast_hour);
}

struct QueryParams {
    mofis::Parameter parameter;
    mofis::LevelType level_type;
    mofis::Level level;
    std::string name;
};


int main() {
    std::vector<QueryParams> production_list = {
        {{{{"discipline", 0}, {"parameterCategory", 3}, {"parameterNumber", 5}}},{}, {}, "HGT"},
        {{"2t"}, {}, {}, "2T"},
        {{"2r"}, {}, {}, "2RH"},
        {{"10u"}, {}, {}, "10U"},
        {{"10v"}, {}, {}, "10V"},
        {{{{"discipline", 0}, {"parameterCategory", 2}, {"parameterNumber", 22}}},{}, {10}, "10FG1"},
        {{{{"discipline", 0}, {"parameterCategory", 1}, {"parameterNumber", 3}}},{}, {}, "PWV"},
        {{{{"discipline", 0}, {"parameterCategory", 19}, {"parameterNumber", 0}}},{}, {}, "VIS"},
        {{{{"discipline", 0}, {"parameterCategory", 3}, {"parameterNumber", 0}}},{}, {}, "SP"},
        {{"t"}, {"surface"}, {}, "SKT"},
        {{{{"discipline", 0}, {"parameterCategory", 6}, {"parameterNumber", 1}}},{}, {}, "TCC"},
        {{{{"discipline", 0}, {"parameterCategory", 6}, {"parameterNumber", 3}}},{}, {}, "LCC"},
        {{{{"discipline", 0}, {"parameterCategory", 1}, {"parameterNumber", 8}}},{}, {}, "TP"},
        {{{{"discipline", 0}, {"parameterCategory", 1}, {"parameterNumber", 29}}},{}, {}, "SF"},
        {{"2d"}, {}, {}, "2D"},
        {{{{"discipline", 0}, {"parameterCategory", 3}, {"parameterNumber", 225}}},{"surface"}, {}, "DEG0L"},
        {{{{"discipline", 0}, {"parameterCategory", 16}, {"parameterNumber", 224}}},{"surface"}, {}, "CRR"},
        {{{{"discipline", 0}, {"parameterCategory", 1}, {"parameterNumber", 19}}},{}, {}, "PTYPE"},

        {{"t"}, {"isobaricInhPa"}, {925}, "925T"},
        {{"t"}, {"isobaricInhPa"}, {850}, "850T"},
        {{"t"}, {"isobaricInhPa"}, {800}, "800T"},
        {{"t"}, {"isobaricInhPa"}, {700}, "700T"},
        {{"t"}, {"isobaricInhPa"}, {500}, "500T"},

        {{"q"}, {"isobaricInhPa"}, {925}, "925Q"},
        {{"q"}, {"isobaricInhPa"}, {850}, "850Q"},
        {{"q"}, {"isobaricInhPa"}, {800}, "800Q"},
        {{"q"}, {"isobaricInhPa"}, {700}, "700Q"},
        {{"q"}, {"isobaricInhPa"}, {500}, "500Q"},

        {{"gh"}, {"isobaricInhPa"}, {925}, "925GH"},
        {{"gh"}, {"isobaricInhPa"}, {850}, "850GH"},
        {{"gh"}, {"isobaricInhPa"}, {800}, "800GH"},
        {{"gh"}, {"isobaricInhPa"}, {700}, "700GH"},
        {{"gh"}, {"isobaricInhPa"}, {500}, "500GH"},

        {{"u"}, {"isobaricInhPa"}, {925}, "925U"},
        {{"u"}, {"isobaricInhPa"}, {850}, "850U"},
        {{"u"}, {"isobaricInhPa"}, {800}, "800U"},
        {{"u"}, {"isobaricInhPa"}, {700}, "700U"},
        {{"u"}, {"isobaricInhPa"}, {500}, "500U"},

        {{"v"}, {"isobaricInhPa"}, {925}, "925V"},
        {{"v"}, {"isobaricInhPa"}, {850}, "850V"},
        {{"v"}, {"isobaricInhPa"}, {800}, "800V"},
        {{"v"}, {"isobaricInhPa"}, {700}, "700V"},
        {{"v"}, {"isobaricInhPa"}, {500}, "500V"},

        {{"wz"}, {"isobaricInhPa"}, {925}, "925W"},
        {{"wz"}, {"isobaricInhPa"}, {850}, "850W"},
        {{"wz"}, {"isobaricInhPa"}, {800}, "800W"},
        {{"wz"}, {"isobaricInhPa"}, {700}, "700W"},
        {{"wz"}, {"isobaricInhPa"}, {500}, "500W"},

        {{"r"}, {"isobaricInhPa"}, {925}, "925R"},
        {{"r"}, {"isobaricInhPa"}, {850}, "850R"},
        {{"r"}, {"isobaricInhPa"}, {800}, "800R"},
        {{"r"}, {"isobaricInhPa"}, {700}, "700R"},
        {{"r"}, {"isobaricInhPa"}, {500}, "500R"},
    };

    auto count = 0;
    auto product_count = production_list.size();
    for(const auto& query: production_list) {
        count ++;

        auto parameter = query.parameter;
        auto level_type = query.level_type;
        auto level = query.level;
        auto product_name = query.name;

        for(auto forecast_hour = 0; forecast_hour <= 24; forecast_hour++) {
            auto file_path = get_file_path(forecast_hour);
            fmt::print(
                "[{count:02d}/{total}][{name:<5}][{forecast_hour:02d}] file path: {file_path}\n",
                "count"_a=count, "total"_a=product_count, "name"_a=product_name, "forecast_hour"_a=forecast_hour, "file_path"_a=file_path);

            auto handler = meso_1km_post::load_message_from_file(file_path, parameter, level_type, level);

            if (handler == nullptr) {
                fmt::print(std::cerr, "[{count:02d}][{name:<5}][{forecast_hour:02d}] ERROR: message not found!\n", count, forecast_hour);
                continue;
            }

            long discipline = -1;
            auto err = codes_get_long(handler, "discipline", &discipline);
            if (err != 0) {
                fmt::print(std::cerr, "codes_get_long has error: {}\n", err);
            }

            codes_handle_delete(handler);
        }
    }

    return 0;
}
