#include <game/time.hpp>
#include <game/utils.hpp>
#include <game/shader.hpp>

#include <GLFW/glfw3.h>

int main() {
    gm::duration delta_time;
    gm::time_point time, last_tick_time{gm::get_time()};

    GLFWwindow* window = gm::setup_glfw(1280, 720, "PG Game");

    GLuint shader =  gm::make_shader_program("main.vert", "main.frag");

    // Since it is the only shader program we'll use it is better to bind it here
    glUseProgram(shader);

    while (!glfwWindowShouldClose(window)) {
        time = gm::get_time();
        delta_time = time - last_tick_time;

        glfwPollEvents();

        // render(delta_time.count(), window);

        if (delta_time >= gm::TICK_STEP) {
            // update_state();

            last_tick_time = time;
        }
    }

    // Unload shader program
    glUseProgram(0);

    glfwTerminate();

    return 0;
}
