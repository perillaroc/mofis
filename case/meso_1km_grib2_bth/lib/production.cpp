#include "production.h"

#include <fmt/format.h>

std::string grib2_bth::get_file_path(int forecast_hour) {
    //    auto file_template = "/g2/nwp_sp/OPER_ARCHIVE/GRAPES_MESO_1KM/Prod-grib/2022030700/ORIG/rmf.hgra.2022030700{:03}.grb2";
    auto file_template = "/g11/wangdp/project/work/data/playground/winter/grid-bth/data/2022030700/ORIG/rmf.hgra.2022030700{:03}.grb2";
    return fmt::format(file_template, forecast_hour);
}

std::vector<grib2_bth::QueryParams> grib2_bth::get_production_list() {
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

    return production_list;
}
