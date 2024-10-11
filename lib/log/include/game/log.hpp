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
}
