#pragma once

#include <cstdint>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace gm {

const uint16_t WINDOW_WIDTH  = 1280;
const uint16_t WINDOW_HEIGHT = 720;

const GLfloat WORLD_WIDTH  = 640;
const GLfloat WORLD_HEIGHT = 360;

GLFWwindow* init_context(int width, int height, std::string title);
void terminate();

void glfw_error_callback(int code, const char* desc);
void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height);

}
