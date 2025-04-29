cmake_minimum_required(VERSION 3.10)
project(lld_cpp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add parking lot projects
add_subdirectory(examples/parking_lot)
add_subdirectory(examples/parking_lot_v2) 