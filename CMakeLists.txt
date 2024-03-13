cmake_minimum_required(VERSION 3.10)
project(MyMPIProject)

# Find MPI package
find_package(MPI REQUIRED)

# Add include directories for MPI
include_directories(${MPI_INCLUDE_PATH})

# Add your source files
set(SOURCES 
    Mpi_identity.cpp 
    RMA_linear_bcast.cpp 
    RMA_binary_bcast.cpp 
    RMA_binomial_bcast.cpp 
    benchmark.cpp
    main.cpp
)

# Add the executable
add_executable(main ${SOURCES})

# Link MPI libraries
target_link_libraries(main ${MPI_CXX_LIBRARIES})