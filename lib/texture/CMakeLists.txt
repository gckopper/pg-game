cmake_minimum_required(VERSION 3.25)

project(texture)

add_library(${PROJECT_NAME} STATIC "src/texture.cpp" "include/game/texture.hpp")

target_link_libraries(${PROJECT_NAME} glad log stb)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC "include")
