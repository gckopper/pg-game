cmake_minimum_required(VERSION 3.25)

project(types)

add_library(${PROJECT_NAME} INTERFACE "include/game/types.hpp")

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${PROJECT_NAME} INTERFACE "include")
