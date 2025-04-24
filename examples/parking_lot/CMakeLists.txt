add_executable(parking_lot
    src/main.cpp
    src/parking_lot.cpp
)

target_include_directories(parking_lot
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
) 