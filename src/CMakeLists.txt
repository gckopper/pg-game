add_executable(main main.cpp)

target_link_libraries(main glfw types sprite state time utils render "$<$<NOT:$<PLATFORM_ID:Emscripten>>:glad>")

install(TARGETS main DESTINATION ${CMAKE_INSTALL_PREFIX})
install(DIRECTORY shaders DESTINATION ${CMAKE_INSTALL_PREFIX})

if(EMSCRIPTEN)
    set_target_properties(main PROPERTIES SUFFIX ".html")
    set(LFLAGS "-s USE_GLFW=3 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s NO_EXIT_RUNTIME=0 -s ASSERTIONS=1 -s SINGLE_FILE --preload-file ${PROJECT_SOURCE_DIR}/src/shaders@src/shaders --preload-file ${PROJECT_SOURCE_DIR}/assets@assets -sFULL_ES3")
    set_target_properties(main PROPERTIES LINK_FLAGS "${LFLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LFLAGS}")
    message("${LFLAGS}")
endif()
