add_executable(main main.cpp)

target_link_libraries(main glad glfw types sprite state time utils render)

install(TARGETS main DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY shaders DESTINATION ${CMAKE_INSTALL_PREFIX})
