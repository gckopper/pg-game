#pragma once

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#else
#include <glad/glad.h>
#endif
#include <iostream>

#ifdef DEBUG 
#define LOG(X) std::cerr << X << std::endl; 
#else
#define LOG(X) 
#endif

namespace gm {
    void log_shader(GLuint shader);
    void log_program(GLuint program);
    //GLenum glCheckError_(const char *file, int line);
}

#define glCheckError() gm::glCheckError_(__FILE__, __LINE__)
