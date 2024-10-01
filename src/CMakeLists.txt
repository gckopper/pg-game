add_executable(main main.cpp)

target_link_libraries(main glad glfw time shader)

install(TARGETS main DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY shaders DESTINATION ${CMAKE_INSTALL_PREFIX})