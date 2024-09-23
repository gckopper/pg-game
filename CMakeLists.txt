cmake_minimum_required(VERSION 3.25)

project(pg-game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Og -g -pedantic")
endif()

add_subdirectory("extern/glad")
add_subdirectory("extern/glfw")
add_subdirectory("src")
add_subdirectory("lib")
