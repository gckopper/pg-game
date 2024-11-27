cmake_minimum_required(VERSION 3.25)

project(shader)

add_library(${PROJECT_NAME} STATIC "include/game/shader.hpp" "src/shader.cpp")

target_link_libraries(${PROJECT_NAME} log utils "$<$<NOT:$<PLATFORM_ID:Emscripten>>:glad>")

target_include_directories(${PROJECT_NAME} PUBLIC "include")
