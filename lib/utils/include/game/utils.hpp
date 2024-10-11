#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gm {

const GLfloat WORLD_WIDTH  = 640;
const GLfloat WORLD_HEIGHT = 360;

GLFWwindow* setup_glfw(int width, int height, std::string title);
void terminate();

}
