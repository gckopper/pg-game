#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <game/types.hpp>

namespace gm {

struct Input {
    Coordinate movement;
    bool attack;
};

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

Input get_input(float speed);

void stop_attack();

} // namespace gm
