#include <iostream>
#include <vector>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include <production.h>

using namespace fmt::literals;


int main() {
    auto output_directory = "/g11/wangdp/project/work/data/playground/winter/grid-bth/output/serial";

    auto production_list = grib2_bth::get_production_list();

    auto count = 0;
    auto product_count = production_list.size();
    for(const auto& query: production_list) {
        count ++;

        auto parameter = query.parameter;
        auto level_type = query.level_type;
        auto level = query.level;
        auto product_name = query.name;

        auto output_file_path = fmt::format("{}/{}.grb2", output_directory, product_name);
        auto output_file = std::fopen(output_file_path.c_str(), "wb");

        for(auto forecast_hour = 0; forecast_hour <= 24; forecast_hour++) {
            auto file_path = grib2_bth::get_file_path(forecast_hour);
            fmt::print(
                "[{count:02d}/{total}][{name:<5}][{forecast_hour:02d}] file path: {file_path}\n",
                "count"_a=count, "total"_a=product_count, "name"_a=product_name, "forecast_hour"_a=forecast_hour, "file_path"_a=file_path);

            auto handler = meso_1km_post::load_message_from_file(file_path, parameter, level_type, level);
            if (handler == nullptr) {
                fmt::print(std::cerr, "[{count:02d}][{name:<5}][{forecast_hour:02d}] ERROR: message not found!\n", count, forecast_hour);
                continue;
            }

            int err = 0;

            size_t total_length = 0;
            err = codes_get_message_size(handler, &total_length);
            if (err != 0) {
                fmt::print(std::cerr, "codes_get_message_size has error: {}\n", err);
                codes_handle_delete(handler);
                continue;
            }

            const void* buffer = nullptr;

            size_t size = 0;
            err = codes_get_message(handler, &buffer, &size);
            if (err != 0) {
                fmt::print(std::cerr, "codes_get_message has error: {}\n", err);
                codes_handle_delete(handler);
                continue;
            }
//            fmt::print("totalLength {} size {}\n", total_length, size);

            std::fwrite(buffer, sizeof(char), total_length*sizeof(char), output_file);

            codes_handle_delete(handler);
        }

        std::fclose(output_file);
    }

    return 0;
}
