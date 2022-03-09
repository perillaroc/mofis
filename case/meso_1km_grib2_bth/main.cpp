#include <iostream>
#include <cstdio>

#include <message.h>

int main() {
    std::cout << "Hello, World!" << std::endl;

    std::string file_path = "/g2/nwp_sp/OPER_ARCHIVE/GRAPES_MESO_1KM/Prod-grib/2022030700/ORIG/rmf.hgra.2022030700002.grb2";

    mofis::Parameter parameter;
    parameter.keys = {
            {"discipline", 0},
            {"parameterCategory", 3},
            {"parameterNumber", 225}
    };

    mofis::LevelType level_type;
    level_type.name = "surface";

    mofis::Level level;

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
