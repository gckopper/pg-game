#include <cstdint>
#include <iostream>
#include <random>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <game/input.hpp>
#include <game/render.hpp>
#include <game/state.hpp>
#include <game/time.hpp>
#include <game/types.hpp>
#include <game/utils.hpp>

int main() {
    GLFWwindow* window = gm::init_context(gm::WINDOW_WIDTH, gm::WINDOW_HEIGHT, "PG Game");

    gm::Entities entities;
    gm::setup_entities(entities);

    gm::Background background;
    gm::setup_background(background);

    gm::Healthbar healthbar;
    gm::setup_healthbar(healthbar);

    gm::Font font;
    gm::setup_font(font);

    gm::add_text(" !\"#$%", {0.f, gm::WORLD_HEIGHT - 20.0f}, 10.0f, font);
    gm::add_text("pqrstuv", {0.f, 0.0f}, 8.0f, font);

    std::cout << font.offset << '\n';

    gm::Input input;

    std::random_device rd;
    std::mt19937 gen = std::mt19937(rd());
    std::uniform_int_distribution<uint64_t> spawn_distribution(0, 15);

    uint64_t elapsed_ticks = 0;

    gm::duration delta_time;
    gm::time_point current_time, last_tick_time{gm::get_time()};

    while (!glfwWindowShouldClose(window) && entities.player.health > 0) {
        current_time = gm::get_time();
        delta_time = current_time - last_tick_time;

        if (delta_time >= gm::TICK_STEP) {
            if (spawn_distribution(gen) + std::log2(elapsed_ticks) > 15) {
                gm::spawn_enemy(entities, gen);
            }

            input = gm::get_input(entities.player);

            gm::update_sprites(entities, input);
            gm::update_background(background, input);

            gm::player_attack(entities);
            for (uint8_t i = 0; i < entities.enemy_count; ++i) {
                if (entities.enemies[i].health < gm::make_enemy(entities.enemies[i].type, {}).health) {
                    entities.enemies[i].hitbox.pos += {10000.0f, 0.0f};
                    entities.enemies[i].tex_pos    += {10000.0f, 0.0f};
                    entities.enemies[i].delta_pos  += {10000.0f, 0.0f};
                }
            }
            gm::enemy_attack(entities, healthbar);

            gm::move_enemies(entities, input.movement);
            gm::update_vbo(entities);

            ++elapsed_ticks;
            
            gm::time_t ratio = delta_time / gm::TICK_STEP;
            delta_time     -= ratio * gm::TICK_STEP;
            last_tick_time += ratio * gm::TICK_STEP;
        }

        gm::render(delta_time.count(), entities, background, healthbar, font);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
