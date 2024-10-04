#include <game/log.hpp>

#include <GLFW/glfw3.h>
#include <cstdlib>

void gm::terminate() {
    glfwTerminate();
    std::abort();
}

void gm::log_shader(GLuint shader) {
    int success;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &success);
    std::string log(success, ' ');
    glGetShaderInfoLog(shader, success, NULL, log.data());
    LOG("Shader operation failed with error: " << log);
}

void gm::log_program(GLuint program) {
    int success;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &success);
    std::string log(success, ' ');
    glGetProgramInfoLog(program, success, NULL, log.data());
    LOG("Program operation failed with error: " << log);
}
