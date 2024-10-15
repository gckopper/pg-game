#include <chrono>
#include <cstdint>
#include <format>
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


    std::cout << font.offset << '\n';

    gm::Input input;

    std::random_device rd;
    std::mt19937 gen = std::mt19937(rd());
    std::uniform_int_distribution<uint64_t> spawn_distribution(0, 15);

    uint64_t elapsed_ticks = 0;
    gm::time_point game_start;

    gm::duration delta_time;
    gm::time_point current_time, last_tick_time{gm::get_time()};

    uint64_t screen = 0;
    uint64_t enemies_killed = 0;
    gm::add_text("Press <space> to start", {gm::WORLD_WIDTH/2 - 176.0f, gm::WORLD_HEIGHT/2.0f - 8.0f}, 16.0f, font);

    while (!glfwWindowShouldClose(window)) {
        current_time = gm::get_time();
        delta_time = current_time - last_tick_time;
        switch (screen) {
        case 0:
            input = gm::get_input(entities.player);
            gm::render(font);
            if (input.attack) {
                gm::clear_text(font);
                screen = 1;
                game_start = gm::get_time();
            }
            break;
        case 1:
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
                        enemies_killed++;
                    }
                }
                gm::enemy_attack(entities, healthbar);

                gm::move_enemies(entities, input.movement);
                gm::update_vbo(entities);

                if (entities.player.health <= 0) {
                    gm::clear_text(font);
                    gm::add_text("GAME OVER", {gm::WORLD_WIDTH/2 - 72.0f, gm::WORLD_HEIGHT/2.0f - 8.0f}, 16.0f, font);
                    std::string kill_count = "Kills: " + std::to_string(enemies_killed); 
                    gm::add_text(kill_count, gm::Coordinate(gm::WORLD_WIDTH/2 - 8.0f * (kill_count.size()/2), gm::WORLD_HEIGHT/2.0f - 32.0f), 8.0f, font);
                    std::string time = std::format("Survived: {:%M:%S}", std::chrono::duration_cast<std::chrono::seconds>(current_time - game_start));
                    gm::add_text(time, {gm::WORLD_WIDTH/2 - 8.0f * (time.size()/2), gm::WORLD_HEIGHT/2.0f - 56.0f}, 8.0f, font);
                    gm::add_text("Press <escape> to exit", {gm::WORLD_WIDTH/2 - 88.0f, gm::WORLD_HEIGHT/2.0f - 80.0f}, 8.0f, font);
                    screen = 2;
                }

                ++elapsed_ticks;
                
                gm::time_t ratio = delta_time / gm::TICK_STEP;
                delta_time     -= ratio * gm::TICK_STEP;
                last_tick_time += ratio * gm::TICK_STEP;
            }
            gm::render(delta_time.count(), entities, background, healthbar, font);
            break;
        case 2:
            gm::render(font);
            break;
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
