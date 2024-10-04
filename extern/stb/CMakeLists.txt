cmake_minimum_required(VERSION 3.25)

project(stb)

add_library(${PROJECT_NAME} INTERFACE include/stb/stb_image.h)

target_include_directories(${PROJECT_NAME} INTERFACE include)
