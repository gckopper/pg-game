cmake_minimum_required(VERSION 3.25)

project(render)

add_library(${PROJECT_NAME} STATIC "src/render.cpp" "include/game/render.hpp")

target_link_libraries(${PROJECT_NAME} types time "$<$<NOT:$<PLATFORM_ID:Emscripten>>:glad>")

target_include_directories(${PROJECT_NAME} PUBLIC "include")
