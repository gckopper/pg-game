cmake_minimum_required(VERSION 3.25)

project(input)

add_library(${PROJECT_NAME} STATIC "include/game/input.hpp" "src/input.cpp")

target_link_libraries(${PROJECT_NAME} glad log types)

target_include_directories(${PROJECT_NAME} PUBLIC "include")
