project(bth)

find_package(fmt REQUIRED)

add_library(bth STATIC production.cpp production.h)

target_include_directories(bth INTERFACE .)
target_link_libraries(bth PUBLIC mofis_grib fmt::fmt)