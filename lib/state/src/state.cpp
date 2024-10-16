#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <span>

#include <glad/glad.h>

#include <game/sprite.hpp>
#include <game/state.hpp>
#include <game/types.hpp>
#include <game/utils.hpp>

void gm::move_enemies(Entities &entities, Coordinate& player_movement) {
    // update movement from last tick
    for (uint8_t i = 0; i < entities.enemy_count; ++i) {
        entities.enemies[i].hitbox.pos += entities.enemies[i].delta_pos;
        entities.enemies[i].tex_pos    += entities.enemies[i].delta_pos;
    }
    
    // sort by distance to player
    std::sort(entities.enemies.begin(), entities.enemies.begin() + entities.enemy_count, [&](const Enemy& lhs, const Enemy& rhs) {
        Coordinate lhs_delta = lhs.hitbox.pos - entities.player.hitbox.pos;
        lhs_delta *= lhs_delta;

        Coordinate rhs_delta = rhs.hitbox.pos - entities.player.hitbox.pos;
        rhs_delta *= rhs_delta;
        
        return lhs_delta.x + lhs_delta.y < rhs_delta.x + rhs_delta.y;
    });

    Player& p = entities.player;

    // despawn enemies
    for (int8_t i = entities.enemy_count - 1; i >= 0; --i) {
        Coordinate dist = entities.enemies[i].hitbox.pos - p.hitbox.pos;

        if (std::abs(dist.x) > DESPAWN_DISTANCE_X || std::abs(dist.y) > DESPAWN_DISTANCE_Y) {
            --entities.enemy_count;
        }
    }

    // movement
    for (uint8_t i = 0; i < entities.enemy_count; ++i) {
        Enemy& e = entities.enemies[i];
        
        Coordinate original_pos = e.hitbox.pos;
        Coordinate delta = p.hitbox.pos - e.hitbox.pos;

        GLfloat inv_hip = quake_rsqrt(delta.x * delta.x + delta.y * delta.y);
        GLfloat dist = std::min(e.speed, 1.0f / inv_hip);

        delta = {dist * inv_hip * delta.x, dist * inv_hip * delta.y};
        e.hitbox.pos += delta;

        // collision
        for (uint8_t j = 0; j < entities.enemy_count; ++j) {
            Enemy& e2 = entities.enemies[j];
            
            if (!colliding(e.hitbox, e2.hitbox) || j == i) continue;

            GLfloat intersect_x = (original_pos.x > e2.hitbox.pos.x ? e2.hitbox.width : e.hitbox.width)   - std::abs(e.hitbox.pos.x - e2.hitbox.pos.x);
            GLfloat intersect_y = (original_pos.y > e2.hitbox.pos.y ? e2.hitbox.height : e.hitbox.height) - std::abs(e.hitbox.pos.y - e2.hitbox.pos.y);

            if (intersect_x / e2.hitbox.width * e2.hitbox.height < intersect_y) {
                e.hitbox.pos.x += ((original_pos.x > e2.hitbox.pos.x) ? intersect_x : -intersect_x);
            } else {
                e.hitbox.pos.y += ((original_pos.y > e2.hitbox.pos.y) ? intersect_y : -intersect_y);
            }
        }

        e.delta_pos = e.hitbox.pos - original_pos;
    }

    for (uint8_t i = 0; i < entities.enemy_count; ++i) {
        entities.enemies[i].hitbox.pos -= entities.enemies[i].delta_pos;
        entities.enemies[i].delta_pos -= player_movement;
    }
}

void gm::update_vbo(Entities& entities) {
    std::span<GLfloat> vbo_data = entities.vbo_data;

    constexpr auto sprite_offset = [](uint8_t sprite_tick) -> GLfloat {
        uint16_t res = (sprite_tick / SPRITE_STEP) * SPRITE_SIZE;
        return static_cast<GLfloat>(res);
    };

    const auto update_tex = [&](const uint16_t offset, const uint8_t sprite_tick, const uint16_t atlas_pos) -> void {
        vbo_data[offset + 2]  = (sprite_offset(sprite_tick) + SPRITE_SIZE) / static_cast<GLfloat>(ATLAS_WIDTH);
        vbo_data[offset + 3]  = (atlas_pos + SPRITE_SIZE)                  / static_cast<GLfloat>(ATLAS_HEIGHT);
        vbo_data[offset + 8]  = (sprite_offset(sprite_tick) + SPRITE_SIZE) / static_cast<GLfloat>(ATLAS_WIDTH);
        vbo_data[offset + 9]  = atlas_pos                  / static_cast<GLfloat>(ATLAS_HEIGHT);
        vbo_data[offset + 14] = sprite_offset(sprite_tick) / static_cast<GLfloat>(ATLAS_WIDTH);
        vbo_data[offset + 15] = atlas_pos                  / static_cast<GLfloat>(ATLAS_HEIGHT);
        vbo_data[offset + 20] = sprite_offset(sprite_tick) / static_cast<GLfloat>(ATLAS_WIDTH);
        vbo_data[offset + 21] = (atlas_pos + SPRITE_SIZE)                  / static_cast<GLfloat>(ATLAS_HEIGHT);
    };

    const auto update_tex_flipped = [&](const uint16_t offset, const uint8_t sprite_tick, const uint16_t atlas_pos) -> void {
        vbo_data[offset + 2]  = sprite_offset(sprite_tick) / static_cast<GLfloat>(ATLAS_WIDTH);
        vbo_data[offset + 3]  = (atlas_pos + SPRITE_SIZE)                  / static_cast<GLfloat>(ATLAS_HEIGHT);
        vbo_data[offset + 8]  = sprite_offset(sprite_tick) / static_cast<GLfloat>(ATLAS_WIDTH);
        vbo_data[offset + 9]  = atlas_pos                  / static_cast<GLfloat>(ATLAS_HEIGHT);
        vbo_data[offset + 14] = (sprite_offset(sprite_tick) + SPRITE_SIZE) / static_cast<GLfloat>(ATLAS_WIDTH);
        vbo_data[offset + 15] = atlas_pos                  / static_cast<GLfloat>(ATLAS_HEIGHT);
        vbo_data[offset + 20] = (sprite_offset(sprite_tick) + SPRITE_SIZE) / static_cast<GLfloat>(ATLAS_WIDTH);
        vbo_data[offset + 21] = (atlas_pos + SPRITE_SIZE)                  / static_cast<GLfloat>(ATLAS_HEIGHT);
    };

    // player texture
    if (entities.player.sprite_flipped) {
        update_tex_flipped(0, entities.player.sprite_tick, entities.player.sprite->ATLAS_POS);
    } else {
        update_tex(0, entities.player.sprite_tick, entities.player.sprite->ATLAS_POS);
    }

    for (uint16_t i = 0; i < entities.enemy_count; ++i) {
        Enemy& e = entities.enemies[i];
        
        const uint16_t offset = (i + 1) * 24;
        
        // vertex positions (tr -> br -> bl -> tl)
        vbo_data[offset]      = e.tex_pos.x + SPRITE_SIZE;
        vbo_data[offset + 1]  = e.tex_pos.y + SPRITE_SIZE;
        vbo_data[offset + 6]  = e.tex_pos.x + SPRITE_SIZE;
        vbo_data[offset + 7]  = e.tex_pos.y;
        vbo_data[offset + 12] = e.tex_pos.x;
        vbo_data[offset + 13] = e.tex_pos.y;
        vbo_data[offset + 18] = e.tex_pos.x;
        vbo_data[offset + 19] = e.tex_pos.y + SPRITE_SIZE;

        // texture positions
        if (e.sprite_flipped) {
            update_tex_flipped(offset, e.sprite_tick, e.sprite->ATLAS_POS);
        } else {
            update_tex(offset, e.sprite_tick, e.sprite->ATLAS_POS);
        }

        // delta pos
        for (uint8_t j = 0; j < 4; ++j) {
            vbo_data[offset + 4 + j * 6] = e.delta_pos.x;
            vbo_data[offset + 5 + j * 6] = e.delta_pos.y;
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, entities.vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, (entities.enemy_count + 1) * 24 * sizeof(GLfloat), entities.vbo_data.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void gm::player_attack(Entities& entities) {
    if (entities.player.sprite != &sprites::PLAYER_ATTACK || entities.player.sprite_tick / SPRITE_STEP < 3) return;

    Hitbox left  = {.pos = {0.0f, std::ceil((WORLD_HEIGHT - SPRITE_SIZE) / 2.0f) + 7}, .width = 20, .height = 13};
    Hitbox right = {.pos = {0.0f, std::ceil((WORLD_HEIGHT - SPRITE_SIZE) / 2.0f) + 7}, .width = 20, .height = 25};

    if (entities.player.sprite_flipped) {
        left.pos.x =  std::ceil((WORLD_WIDTH  - SPRITE_SIZE) / 2.0f) + 18;
        right.pos.x = std::ceil((WORLD_WIDTH  - SPRITE_SIZE) / 2.0f) - 2;
    } else {
        left.pos.x  = std::ceil((WORLD_WIDTH  - SPRITE_SIZE) / 2.0f) + 3;
        right.pos.x = std::ceil((WORLD_WIDTH  - SPRITE_SIZE) / 2.0f) + 23;
    }

    for (uint8_t i = 0; i < entities.enemy_count; ++i) {
        if (colliding(entities.enemies[i].hitbox, left) || colliding(entities.enemies[i].hitbox, right)) {
            entities.enemies[i].health = std::max(0, entities.enemies[i].health - entities.player.attack);
        }
    }
}

void gm::enemy_attack(Entities& entities, Healthbar& healthbar) {
    int16_t highest_attack = 0;

    for (uint8_t i = 0; i < entities.enemy_count; ++i) {
        if (!colliding(entities.enemies[i].hitbox, entities.player.hitbox)) continue;

        highest_attack = std::max(highest_attack, entities.enemies[i].attack);
    }

    if (highest_attack > 0) {
        entities.player.health -= highest_attack;

        glUseProgram(healthbar.shader_program);
        glUniform1f(healthbar.u_health_percentage, entities.player.health / static_cast<GLfloat>(PLAYER_MAX_HEALTH));
        glUseProgram(0);
    }

}

void gm::update_background(Background& background, Input& input) {
    Coordinate normalized;
    normalized.x = input.movement.x / background.texture_width;
    normalized.y = input.movement.y / background.texture_height;
    for (uint8_t i = 0; i < 24; i+=6) {
        background.vbo_data[2+i] = normalized.x;
        background.vbo_data[3+i] = normalized.y;
    }
    glBindBuffer(GL_ARRAY_BUFFER, background.vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, background.vbo_data.size() * sizeof(GLfloat), background.vbo_data.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    for (uint8_t i = 0; i < 24; i+=6) {
        background.vbo_data[4+i] += normalized.x;
        background.vbo_data[5+i] += normalized.y;
    }
}

void gm::spawn_enemy(Entities& entities, std::mt19937& gen) {
    if (entities.enemy_count >= MAX_ENEMIES) return;

    std::uniform_int_distribution<> rand_side(0, 3);
    std::uniform_real_distribution<> rand_x(0, SPAWN_OFFSET_X*2 + gm::WORLD_WIDTH);
    std::uniform_real_distribution<> rand_y(0, SPAWN_OFFSET_Y*2 + gm::WORLD_HEIGHT);
    Coordinate pos;

    switch (rand_side(gen)) {
        case 0:
            pos.x = rand_x(gen);
            pos.y = -SPAWN_OFFSET_Y;
            break;
        case 1:
            pos.x = rand_x(gen);
            pos.y = gm::WORLD_HEIGHT + SPAWN_OFFSET_Y;
            break;
        case 2:
            pos.x = -SPAWN_OFFSET_X;
            pos.y = rand_y(gen);
            break;
        case 3:
            pos.x = gm::WORLD_WIDTH + SPAWN_OFFSET_X;
            pos.y = rand_y(gen);
            break;
    }

    entities.enemies[entities.enemy_count++] = make_enemy(ORC, pos);
}

void gm::update_sprites(Entities& entities, Input& input) {
    Player& p = entities.player;
    std::span<Enemy> enemies = entities.enemies;

    for (Enemy& e : enemies.subspan(0, entities.enemy_count)) {
        e.sprite_tick = (e.sprite_tick + 1) % (e.sprite->FRAME_COUNT * gm::SPRITE_STEP);
        e.sprite_flipped = e.hitbox.pos.x > entities.player.hitbox.pos.x;
    }

    if ((p.sprite_tick + 1) == (p.sprite->FRAME_COUNT * gm::SPRITE_STEP)) {
        p.attacking = false;
    }
    p.sprite_tick = (p.sprite_tick + 1) % (p.sprite->FRAME_COUNT * gm::SPRITE_STEP);

    if (p.attacking) {
        input.movement.x = 0.f;
        input.movement.y = 0.f;
    } else {
        if (!input.attack && p.sprite == &gm::sprites::PLAYER_ATTACK) {
            entities.player.sprite = &gm::sprites::PLAYER_WALK;
            entities.player.sprite_tick = 0;
        } 
        if (input.movement.x == 0.0f) {
            if (input.movement.y == 0.0f) {
                p.sprite_tick = 0;
            }
        } else {
            p.sprite_flipped = input.movement.x < 0.f;
        }
        if (input.attack) {
            p.sprite = &gm::sprites::PLAYER_ATTACK;
            p.sprite_tick = 0;
            p.attacking = true;
        } 
    }
}
