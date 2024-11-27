#pragma once

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GLES3/gl3.h>
#else
#include <glad/glad.h>
#endif

#include <string>

namespace gm {

#ifdef DEBUG
    const std::string SHADER_PATH = "./src/shaders/";
#else
    const std::string SHADER_PATH = "./shaders/";
#endif

#ifdef __EMSCRIPTEN__
    const std::string SHADER_VERSION = "#version 300 es\nprecision mediump float;\n";
#else
const std::string SHADER_VERSION = "#version 330 core\n";
#endif

std::string load_shader(std::string filename);

GLuint compile_shader(std::string shader_code, GLenum shader_type);

GLuint make_shader_program(std::string vert_path, std::string frag_path);

}
