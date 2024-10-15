cmake_minimum_required(VERSION 3.25)

project(pg-game)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/install")
install(DIRECTORY assets DESTINATION ${CMAKE_INSTALL_PREFIX})

option(DEBUG "Build with debug flags" OFF)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DEBUG ON)
endif()

if(DEBUG)
    message("Configuring game in debug mode")

    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Og -g -pedantic")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
    endif()
else()
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")

        if(WIN32)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -mwindows")
        endif()
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:windows /ENTRY:mainCRTStartup")
    endif()
endif()

add_subdirectory("extern")
add_subdirectory("src")
add_subdirectory("lib")