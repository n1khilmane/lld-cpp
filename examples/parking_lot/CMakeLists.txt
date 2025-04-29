cmake_minimum_required(VERSION 3.10)
project(parking_lot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
    src/Vehicle.cpp
    src/ParkingSpot.cpp
    src/ParkingLot.cpp
    src/main.cpp
)

# Add header files
set(HEADERS
    include/Vehicle.hpp
    include/ParkingSpot.hpp
    include/ParkingLot.hpp
)

# Create executable
add_executable(parking_lot ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(parking_lot PRIVATE include) 