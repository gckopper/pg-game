#include <game/log.hpp>

#include <GLFW/glfw3.h>
#include <cstdlib>

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

GLenum gm::glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}
