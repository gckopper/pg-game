cmake_minimum_required(VERSION 3.25)

project(log)

add_library(${PROJECT_NAME} STATIC "src/log.cpp" "include/game/log.hpp")

target_link_libraries(${PROJECT_NAME} glad glfw)

if(DEBUG)
    target_compile_definitions(${PROJECT_NAME} INTERFACE DEBUG)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC "include")
