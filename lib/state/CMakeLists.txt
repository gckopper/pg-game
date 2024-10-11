cmake_minimum_required(VERSION 3.25)

project(state)

add_library(${PROJECT_NAME} STATIC "include/game/state.hpp" "src/state.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC "include")

target_link_libraries(${PROJECT_NAME} PUBLIC glad entity sprite utils)