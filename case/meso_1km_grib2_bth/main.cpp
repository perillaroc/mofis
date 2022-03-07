#include <iostream>
#include <cstdio>

#include "message.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::string file_path = "/g1/COMMONDATA/OPER/NWPC/GRAPES_GFS_GMF/Prod-grib/2022030700/ORIG/gmf.gra.2022030700072.grb2";

    mofis::Parameter parameter;
    parameter.short_name = "t";

    mofis::LevelType level_type;
    level_type.name = "isobaricInhPa";

    mofis::Level level;
    level.value = 850;

    auto handler = meso_1km_post::load_message_from_file(file_path, parameter, level_type, level);

    if(handler == nullptr) {
        std::cerr<<"message not found";
        return 1;
    }

    std::cout << "get discipline..." << std::endl;
    long discipline = -1;
    auto err = codes_get_long(handler, "discipline", &discipline);
    if (err != 0) {
        std::cerr << "codes_get_long has error: " << err << std::endl;
    }
    std::cout << "discipline: " << discipline << std::endl;

    codes_handle_delete(handler);

    return 0;
}
