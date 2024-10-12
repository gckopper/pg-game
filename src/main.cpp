#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <game/types.hpp>
#include <game/sprite.hpp>
#include <game/state.hpp>
#include <game/time.hpp>
#include <game/utils.hpp>

constexpr uint16_t ENEMY_SPEED = 3;

void update_pos(gm::Enemy& e) {
    e.world_pos.x = uint16_t(e.world_pos.x + e.delta_pos.x) % uint16_t(gm::WORLD_WIDTH);
    e.tex_pos.x = uint16_t(e.tex_pos.x + e.delta_pos.x) % uint16_t(gm::WORLD_WIDTH);
}

int main() {
    GLFWwindow* window = gm::init_context(gm::WINDOW_WIDTH, gm::WINDOW_HEIGHT, "PG Game");

    gm::Entities e;
    gm::setup_entities(e);

    e.enemies[0] = gm::make_enemy(gm::ORC, {100.0f, 180.0f});
    e.enemies[0].delta_pos = {ENEMY_SPEED, 0.0f};

    e.enemies[1] = gm::make_enemy(gm::ORC, {200.0f, 100.0f});
    e.enemies[1].sprite = gm::get_sprite(e.enemies[1].type, gm::DEATH);

    e.enemy_count = 2;

    e.player.sprite = &gm::sprites::PLAYER_ATTACK;

    gm::update_vbo(e);

    glUseProgram(e.shader_program);
    glBindTexture(GL_TEXTURE_2D, e.texture);
    glBindVertexArray(e.vao);

    int frames = 0;
    int ticks = 0;

    gm::duration delta_time;
    gm::time_point current_time, last_tick_time{gm::get_time()};

    gm::time_point prev = last_tick_time;

    while (!glfwWindowShouldClose(window)) {
        current_time = gm::get_time();
        delta_time = current_time - last_tick_time;

        if (delta_time >= gm::TICK_STEP) {
            e.enemies[0].sprite_tick = (e.enemies[0].sprite_tick + 1) % (e.enemies[0].sprite->FRAME_COUNT * gm::SPRITE_STEP);
            update_pos(e.enemies[0]);

            e.enemies[1].sprite_tick = (e.enemies[1].sprite_tick + 1) % (e.enemies[1].sprite->FRAME_COUNT * gm::SPRITE_STEP);
            e.player.sprite_tick = (e.player.sprite_tick + 1) % (e.player.sprite->FRAME_COUNT * gm::SPRITE_STEP);

            gm::update_vbo(e);

            if (gm::colliding(e.player, e.enemies[0])) {
                std::cout << "collision!" << std::endl;
            }

            ++ticks;
            
            gm::time_t ratio = delta_time / gm::TICK_STEP;
            delta_time -= ratio * gm::TICK_STEP;
            last_tick_time += ratio * gm::TICK_STEP;
        }

        glUniform1f(glGetUniformLocation(e.shader_program, "delta_time"), GLfloat(delta_time.count()) / GLfloat(gm::TICK_STEP.count()));
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, (1 + e.enemy_count) * 6, GL_UNSIGNED_SHORT, (GLvoid*) 0);

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
