cmake_minimum_required(VERSION 3.25)

project(log)

add_library(${PROJECT_NAME} STATIC "src/log.cpp" "include/game/log.hpp")

target_link_libraries(${PROJECT_NAME} glad glfw)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC "include")
