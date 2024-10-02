#pragma once

#include <glad/glad.h>

#include <string>

namespace gm {

#ifdef DEBUG
    const std::string SHADER_PATH = "./src/shaders/";
#else
    const std::string SHADER_PATH = "./shaders/";
#endif

const std::string SHADER_VERSION = "#version 330 core\n";

std::string load_shader(std::string filename);

GLuint compile_shader(std::string shader_code, GLenum shader_type);

GLuint make_shader_program(std::string vert_path, std::string frag_path);

}
