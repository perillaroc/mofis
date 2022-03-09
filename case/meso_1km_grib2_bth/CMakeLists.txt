project(grib2_bth)

find_package(eccodes REQUIRED)
#find_package(OpenJPEG REQUIRED)

#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()

add_executable(grib2_bth main.cpp)

target_link_libraries(grib2_bth PRIVATE mofis_grib)
