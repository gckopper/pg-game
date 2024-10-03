cmake_minimum_required(VERSION 3.25)

project(utils)

add_library(${PROJECT_NAME} STATIC "src/utils.cpp" "include/game/utils.hpp")

target_link_libraries(${PROJECT_NAME} glad glfw log)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC "include")
