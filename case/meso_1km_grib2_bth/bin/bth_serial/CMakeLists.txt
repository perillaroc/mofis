project(grib2_bth_serial)

find_package(fmt REQUIRED)

add_executable(grib2_bth_serial main.cpp)

target_link_libraries(grib2_bth_serial PRIVATE bth fmt::fmt)
