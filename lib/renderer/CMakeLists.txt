cmake_minimum_required(VERSION 3.25)

project(renderer)

add_library(${PROJECT_NAME} STATIC "src/renderer.cpp" "include/game/renderer.hpp")

target_link_libraries(${PROJECT_NAME} glad glfw log types time)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC "include")
