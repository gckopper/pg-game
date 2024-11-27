#pragma once

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

#include <game/types.hpp>

namespace gm {

struct Input {
    Coordinate movement;
    bool attack;
};

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

Input get_input(Player& player);

} // namespace gm
