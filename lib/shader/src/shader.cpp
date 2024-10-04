#include <algorithm>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>

#include <game/shader.hpp>

#include <game/log.hpp>

std::string gm::load_shader(std::string filename) {
    std::ifstream file(SHADER_PATH + filename, std::ios_base::ate);

    if (!file.is_open()) {
        LOG("Failed to open file " << filename);
        LOG("Are you running the program from the correct location?");
        terminate();
    }

    std::string result(SHADER_VERSION.size() + file.tellg(), ' ');
    std::copy(SHADER_VERSION.begin(), SHADER_VERSION.end(), result.begin());
    file.seekg(0);
    file.read(result.data() + SHADER_VERSION.size(), result.size() - SHADER_VERSION.size());

    return result;
}

GLuint gm::compile_shader(std::string shader_code, GLenum shader_type) {
    GLuint shader = glCreateShader(shader_type);
    if (shader == 0) {
        LOG("Unable to create shader object");
        terminate();
    }
    const GLchar *cstr_source = const_cast<const GLchar *>(shader_code.c_str());
    glShaderSource(shader, 1, &cstr_source, NULL);
    glCompileShader(shader);
    GLint success = 0;
    glGetShaderiv(shader,  GL_COMPILE_STATUS, &success);
    // compilation failed
    if (!success) {
        log_shader(shader);
        terminate();
    }
    return shader;
}

GLuint gm::make_shader_program(std::string vert_path, std::string frag_path) {
    GLuint vert_shader = compile_shader(load_shader(vert_path), GL_VERTEX_SHADER);
    GLuint frag_shader = compile_shader(load_shader(frag_path), GL_FRAGMENT_SHADER);

    GLint success = 0;
    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vert_shader);

    glAttachShader(shaderProgram, frag_shader);

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        log_program(shaderProgram);
        terminate();
    }
    
    return shaderProgram;
}
