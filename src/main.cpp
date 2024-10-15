#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <game/input.hpp>
#include <game/render.hpp>
#include <game/sprite.hpp>
#include <game/state.hpp>
#include <game/time.hpp>
#include <game/types.hpp>
#include <game/utils.hpp>

int main() {
    GLFWwindow* window = gm::init_context(gm::WINDOW_WIDTH, gm::WINDOW_HEIGHT, "PG Game");

    gm::Entities e;
    gm::setup_entities(e);

    std::random_device rd;
    std::mt19937 gen = std::mt19937(rd());
    std::uniform_int_distribution<uint64_t> spawn_distribution(0, 15); 

    gm::update_vbo(e);

    gm::Background bg;
    gm::setup_background(bg);

    gm::Input input;

    int frames = 0;
    int ticks = 0;
    uint64_t tick_cout = 0;

    gm::duration delta_time;
    gm::time_point current_time, last_tick_time{gm::get_time()};

    gm::time_point prev = last_tick_time;

    while (!glfwWindowShouldClose(window)) {
        current_time = gm::get_time();
        delta_time = current_time - last_tick_time;

        if (delta_time >= gm::TICK_STEP) {
            input = gm::get_input(e.player);

            if (spawn_distribution(gen) + std::log2(tick_cout) > 15) {
                gm::spawn_enemy(e, gen);
            }

            gm::update_sprites(e, input);
            gm::update_background(bg, input);

            gm::enemy_attack(e);
            gm::player_attack(e);
            for (uint8_t i = 0; i < e.enemy_count; ++i) {
                if (e.enemies[i].health < gm::make_enemy(e.enemies[i].type, {}).health) {
                    e.enemies[i].hitbox.pos += {10000.0f, 100.0f};
                    e.enemies[i].tex_pos    += {10000.0f, 100.0f};
                }
            }

            gm::move_enemies(e, input.movement);

            gm::update_vbo(e);

            ++ticks;
            ++tick_cout;
            
            gm::time_t ratio = delta_time / gm::TICK_STEP;
            delta_time -= ratio * gm::TICK_STEP;
            last_tick_time += ratio * gm::TICK_STEP;
        }

        gm::render(delta_time.count(), e, bg);

        ++frames;

        if ((current_time - prev) >= std::chrono::seconds(1)) {
            std::cout << "TPS: " << std::fixed << std::setprecision(3) <<  (ticks / float((gm::get_time() - prev).count()) * gm::duration(std::chrono::seconds(1)).count()) << std::endl;
            std::cout << "FPS: " << std::fixed << std::setprecision(3) << (frames / float((gm::get_time() - prev).count()) * gm::duration(std::chrono::seconds(1)).count()) << std::endl;

            ticks = 0;
            frames = 0;
            prev = current_time;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
