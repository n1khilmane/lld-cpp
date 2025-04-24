add_executable(basics
    src/main.cpp
    src/shape.cpp
)

add_executable(lesson1
    lesson1.cpp
)

add_executable(lesson2
    lesson2.cpp
)

add_executable(lesson4
    lesson4.cpp
)

add_executable(lesson5
    lesson5.cpp
)

add_executable(lesson6
    lesson6.cpp
)

add_executable(lesson7
    lesson7.cpp
)

add_executable(lesson8
    lesson8.cpp
)

target_include_directories(basics
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
) 