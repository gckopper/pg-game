cmake_minimum_required(VERSION 3.25)

project(utils)

add_library(${PROJECT_NAME} STATIC "src/utils.cpp" "include/game/utils.hpp")

target_link_libraries(${PROJECT_NAME} glfw log input "$<$<NOT:$<PLATFORM_ID:Emscripten>>:glad>")

target_include_directories(${PROJECT_NAME} PUBLIC "include")
