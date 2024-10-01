#include <game/log.hpp>

#include "GLFW/glfw3.h"
#include <cstdlib>

void gm::terminate() {
    glfwTerminate();
    std::abort();
}
