#pragma once

#include <cstdint>
#include <string>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#else
#include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>

namespace gm {

constexpr uint16_t WINDOW_WIDTH  = 1280;
constexpr uint16_t WINDOW_HEIGHT = 720;

constexpr GLfloat WORLD_WIDTH  = 640;
constexpr GLfloat WORLD_HEIGHT = 360;

GLFWwindow* init_context(int width, int height, std::string title);
void terminate();

void glfw_error_callback(int code, const char* desc);
void glfw_framebuffer_size_callback(GLFWwindow* window, int width, int height);

GLfloat quake_rsqrt(GLfloat num);

}
