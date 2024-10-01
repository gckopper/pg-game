cmake_minimum_required(VERSION 3.25)

project(shader)

add_library(${PROJECT_NAME} STATIC "include/game/shader.hpp" "src/shader.cpp")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC "include")