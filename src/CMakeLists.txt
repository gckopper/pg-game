add_executable(main main.cpp)

target_link_libraries(main glad glfw time)

install(TARGETS main DESTINATION ${CMAKE_INSTALL_PREFIX})