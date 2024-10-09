#pragma once

#include <glad/glad.h>
#include <iostream>

#ifdef DEBUG 
#define LOG(X) std::cerr << X << std::endl; 
#else
#define LOG(X) 
#endif

namespace gm {
    void log_shader(GLuint shader);
    void log_program(GLuint program);
    GLenum glCheckError_(const char *file, int line);
}

#define glCheckError() gm::glCheckError_(__FILE__, __LINE__)
