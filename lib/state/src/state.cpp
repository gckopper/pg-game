#include <cstdint>
#include <span>

#include <glad/glad.h>

#include <game/entity.hpp>
#include <game/sprite.hpp>
#include <game/state.hpp>

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
