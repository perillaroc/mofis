project(grib2_bth)

find_package(fmt REQUIRED)

add_executable(grib2_bth main.cpp)

target_link_libraries(grib2_bth PRIVATE mofis_grib fmt::fmt)
