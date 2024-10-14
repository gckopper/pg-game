#include <algorithm>
#include <cstdint>
#include <span>

#include <glad/glad.h>

#include <game/sprite.hpp>
#include <game/state.hpp>
#include <game/types.hpp>
#include <game/utils.hpp>

void gm::move_enemies(Entities &entities) {
    // update movement from last tick
    for (uint8_t i = 0; i < entities.enemy_count; ++i) {
        entities.enemies[i].world_pos += entities.enemies[i].delta_pos;
        entities.enemies[i].tex_pos   += entities.enemies[i].delta_pos;
    }
    
    // sort by distance to player
    std::sort(entities.enemies.begin(), entities.enemies.begin() + entities.enemy_count, [&](const Enemy& lhs, const Enemy& rhs) {
        Coordinate lhs_delta = lhs.world_pos - entities.player.world_pos;
        lhs_delta *= lhs_delta;

        Coordinate rhs_delta = rhs.world_pos - entities.player.world_pos;
        rhs_delta *= rhs_delta;
        
        return lhs_delta.x + lhs_delta.y < rhs_delta.x + rhs_delta.y;
    });

    Player& p = entities.player;

    // despawn enemies
    // for (int8_t i = entities.enemy_count - 1; i >= 0; --i) {
    //     Coordinate dist = entities.enemies[i].world_pos - p.world_pos;
    //     dist *= dist;

    //     if (dist.x + dist.y > DESPAWN_DISTANCE) {
    //         --entities.enemy_count;
    //     }
    // }

    // movement
    for (uint8_t i = 0; i < entities.enemy_count; ++i) {
        Enemy& e = entities.enemies[i];
        
        Coordinate delta = p.world_pos - e.world_pos;
        GLfloat inv_hip = quake_rsqrt(delta.x * delta.x + delta.y * delta.y);

        GLfloat dist = std::min(e.speed, 1.0f / quake_rsqrt(delta.x * delta.x + delta.y * delta.y));

        delta = {dist * inv_hip * delta.x, dist * inv_hip * delta.y};
        e.world_pos += delta;

        // collision
        for (uint8_t j = 0; j < i; ++j) {
            Enemy& e2 = entities.enemies[j];
            
            if (!colliding(e, e2)) continue;

            Coordinate diff = e.world_pos - e2.world_pos;

            Coordinate x_shift, y_shift;

            if (diff.x > 0.0f) {
                x_shift.x = e2.hitbox_width - diff.x;
            } else {
                x_shift.x = -(e2.hitbox_width + diff.x);
            }
            x_shift.y = x_shift.x * (diff.y / diff.x);

            if (diff.y > 0.0f) {
                y_shift.y = e2.hitbox_height - diff.y;
            } else {
                y_shift.y = -(e2.hitbox_height + diff.y);
            }
            y_shift.x = y_shift.y / (diff.y / diff.x);

            Coordinate delta_x = e.world_pos + x_shift - entities.player.world_pos;
            delta_x *= delta_x;

            Coordinate delta_y = e.world_pos + y_shift - entities.player.world_pos;
            delta_y *= delta_y;

            e.world_pos -= delta;
            if (delta_x.x + delta_x.y < delta_y.x + delta_y.y) {
                delta += x_shift;
            } else {
                delta += y_shift;
            }
            e.world_pos += delta;
        }

        e.world_pos -= delta;
        e.delta_pos = delta;
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
