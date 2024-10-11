cmake_minimum_required(VERSION 3.25)

project(entity)

add_library(${PROJECT_NAME} STATIC "include/game/entity.hpp" "src/entity.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC "include")

target_link_libraries(${PROJECT_NAME} PUBLIC glad shader sprite texture time utils)