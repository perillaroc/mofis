project(grib2_bth_mpi)

find_package(fmt REQUIRED)
find_package(MPI REQUIRED)

add_executable(grib2_bth_mpi main.cpp)

message(STATUS "Run: ${MPIEXEC} ${MPIEXEC_NUMPROC_FLAG} ${MPIEXEC_MAX_NUMPROCS} ${MPIEXEC_PREFLAGS} EXECUTABLE ${MPIEXEC_POSTFLAGS} ARGS")
target_link_libraries(grib2_bth_mpi PUBLIC bth fmt::fmt MPI::MPI_CXX)
