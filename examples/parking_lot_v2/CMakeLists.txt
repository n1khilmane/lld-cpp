cmake_minimum_required(VERSION 3.10)
project(parking_lot_v2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
set(SOURCES
    src/Vehicle.cpp
    src/ParkingSpot.cpp
    src/Payment.cpp
    src/Account.cpp
    src/Entrance.cpp
    src/Exit.cpp
    src/DisplayBoard.cpp
    src/ParkingRate.cpp
    src/ParkingLot.cpp
    src/main.cpp
)

# Add header files
set(HEADERS
    include/Types.hpp
    include/Vehicle.hpp
    include/ParkingSpot.hpp
    include/Payment.hpp
    include/Account.hpp
    include/ParkingTicket.hpp
    include/Entrance.hpp
    include/Exit.hpp
    include/DisplayBoard.hpp
    include/ParkingRate.hpp
    include/ParkingLot.hpp
)

# Create executable
add_executable(parking_lot_v2 ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(parking_lot_v2 PRIVATE include) 