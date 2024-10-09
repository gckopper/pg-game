#include <game/types.hpp>
#include <game/log.hpp>
#include <game/time.hpp>
#include <game/utils.hpp>
#include <game/shader.hpp>
#include <game/renderer.hpp>
#include <game/texture.hpp>

int main() {
    gm::duration delta_time;
    gm::time_point time, last_tick_time{gm::get_time()};

    GLFWwindow* window = gm::setup_glfw(gm::WIDTH, gm::HEIGHT, "PG Game");

    gm::game game;
    

    game.bg.render.shader =  gm::make_shader_program("background.vert", "background.frag");
    game.bg.render.tex = gm::load_texture("assets/background.png");
    game.bg.render.u_tex = glGetUniformLocation(game.bg.render.shader, "our_texture");
    game.bg.render.u_time = glGetUniformLocation(game.bg.render.shader, "time_diff");

    game.entity_render.shader =  gm::make_shader_program("main.vert", "main.frag");
    game.entity_render.tex = gm::load_texture("assets/atlas.png");
    game.entity_render.u_tex = glGetUniformLocation(game.entity_render.shader, "our_texture");
    game.entity_render.u_time = glGetUniformLocation(game.entity_render.shader, "time_diff");
    
    gm::setup_buffers(game);

    while (!glfwWindowShouldClose(window)) {
        time = gm::get_time();
        delta_time = time - last_tick_time;

        glfwPollEvents();

        gm::render(delta_time.count(), window, game);

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
