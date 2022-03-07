project(grib2_bth)

find_package(eccodes REQUIRED)
#find_package(OpenJPEG REQUIRED)

#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

add_executable(grib2_bth parameter.cpp level_type.cpp level.cpp message.cpp main.cpp)

target_include_directories(grib2_bth PRIVATE ${eccodes_BASE_DIR}/include)
target_link_libraries(grib2_bth PRIVATE ${eccodes_BASE_DIR}/lib64/libeccodes.so)
