cmake_minimum_required(VERSION 3.6)
project(labo09)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)

set(SOURCE_FILES main.cpp
        src/ejercicios.cpp
        src/ejercicios.h
        src/risas.cpp
        src/risas.h
        tests/risasTEST.cpp
        tests/tests.cpp
        )

add_executable(labo09 ${SOURCE_FILES})

target_link_libraries(labo09 gtest gtest_main)
