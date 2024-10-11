#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gm {

const GLfloat WORLD_WIDTH  = 640;
const GLfloat WORLD_HEIGHT = 360;

GLFWwindow* setup_glfw(int width, int height, std::string title);
void terminate();

void glfw_error_callback(int code, const char* desc);
void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height);

}
