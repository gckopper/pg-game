#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

namespace gm {
    GLFWwindow* setup_glfw(int width, int height, std::string title);
}
