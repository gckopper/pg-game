#pragma once

#include <game/types.hpp>
#include <GLFW/glfw3.h>

namespace gm {
    void render(uint64_t time_diff, GLFWwindow* window, game g);
}
