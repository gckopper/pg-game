cmake_minimum_required(VERSION 3.25)

project(stb)

add_library(${PROJECT_NAME} STATIC "src/stb_image.c" "include/stb/stb_image.h")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC "include")
