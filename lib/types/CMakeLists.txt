cmake_minimum_required(VERSION 3.25)

project(types)

add_library(${PROJECT_NAME} STATIC "include/game/types.hpp" "src/types.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC "include")

target_link_libraries(${PROJECT_NAME} PUBLIC shader sprite texture time utils "$<$<NOT:$<PLATFORM_ID:Emscripten>>:glad>")
