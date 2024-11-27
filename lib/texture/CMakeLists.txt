cmake_minimum_required(VERSION 3.25)

project(texture)

add_library(${PROJECT_NAME} STATIC "src/texture.cpp" "include/game/texture.hpp")

target_link_libraries(${PROJECT_NAME} stb log utils "$<$<NOT:$<PLATFORM_ID:Emscripten>>:glad>")

target_include_directories(${PROJECT_NAME} PUBLIC "include")
