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
#include <string>
#include <stb/stb_image.h>

namespace gm {
    GLuint load_texture(std::string path);
    GLuint load_texture(std::string path, int* result_width, int* result_height);
}
