#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
    std::uniform_real_distribution<> x_distrib(0, gm::WORLD_WIDTH);
    std::uniform_real_distribution<> y_distrib(0, gm::WORLD_HEIGHT);

    for (int i = 0; i < gm::MAX_ENEMIES; ++i) {
        e.enemies[i] = gm::make_enemy(gm::ORC, {0.0f, 0.0f});
        e.enemies[i].world_pos.x += x_distrib(gen);
        e.enemies[i].world_pos.y += y_distrib(gen);
        e.enemies[i].tex_pos += e.enemies[i].world_pos;
    }
    e.enemy_count = gm::MAX_ENEMIES;

    e.player.sprite = &gm::sprites::PLAYER_ATTACK;

    gm::update_vbo(e);

    gm::Background bg;
    gm::setup_background(bg);

    int frames = 0;
    int ticks = 0;

    gm::duration delta_time;
    gm::time_point current_time, last_tick_time{gm::get_time()};

    gm::time_point prev = last_tick_time;

    while (!glfwWindowShouldClose(window)) {
        current_time = gm::get_time();
        delta_time = current_time - last_tick_time;

        if (delta_time >= gm::TICK_STEP) {
            e.player.sprite_tick = (e.player.sprite_tick + 1) % (e.player.sprite->FRAME_COUNT * gm::SPRITE_STEP);

            gm::move_enemies(e);
            gm::update_vbo(e);

            ++ticks;
            
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

            e.player.sprite_flipped = !e.player.sprite_flipped;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
