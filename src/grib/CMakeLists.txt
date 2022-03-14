project(mofis_grib)

find_package(eccodes REQUIRED)
find_package(fmt REQUIRED)

add_library(mofis_grib STATIC grib_util.cpp level_type.cpp level.cpp parameter.cpp message.cpp)

target_include_directories(mofis_grib INTERFACE .)
target_include_directories(mofis_grib PUBLIC ${eccodes_BASE_DIR}/include)
target_link_libraries(mofis_grib PRIVATE ${eccodes_BASE_DIR}/lib64/libeccodes.so fmt::fmt)