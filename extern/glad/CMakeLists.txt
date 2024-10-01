cmake_minimum_required(VERSION 3.25)

project(glad)

add_library(${PROJECT_NAME} include/glad/glad.h src/glad.c)

target_include_directories(${PROJECT_NAME} PUBLIC include)
