#pragma once

#include <array>
#include <cstdint>

#include <glad/glad.h>

#include <game/sprite.hpp>

namespace gm {

struct coordinate {
    GLfloat x;
    GLfloat y;

    constexpr coordinate operator+(const coordinate& other) const {
        return { this->x + other.x, this->y + other.y };
    }

    constexpr coordinate& operator+=(const coordinate& other) {
        return *this = *this + other;
    }
};

struct player {
    uint16_t health = UINT16_MAX;
    uint16_t attack = UINT16_MAX;

    uint8_t hitbox_width  = 12;
    uint8_t hitbox_height = 18;

    uint8_t attack_cooldown = UINT8_MAX;

    const sprite* sprite = &sprites::PLAYER_WALK;
    uint8_t sprite_tick  = 0;
    bool sprite_flipped  = false;
};

enum enemy_type {
    ORC
};

struct enemy {
    enemy_type type;

    uint16_t health;
    uint16_t attack;

    uint8_t hitbox_width;
    uint8_t hitbox_height;

    coordinate world_pos;
    coordinate tex_pos;
    coordinate delta_pos;

    const sprite* sprite;
    uint8_t sprite_tick;
    bool sprite_flipped;
};

constexpr uint8_t MAX_ENEMIES = 64;

struct entities {
    player player;
    
    std::array<enemy, MAX_ENEMIES> enemies;
    uint8_t enemy_count;

    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLuint texture;

    std::array<GLfloat,  (MAX_ENEMIES + 1) * 24> vbo_data;
    std::array<GLushort, (MAX_ENEMIES + 1) * 6>  ebo_data;

    GLuint shader_program;
};

void setup_entities(entities& entities);

constexpr enemy make_enemy(enemy_type type, coordinate pos) {
    switch (type) {
    case ORC:
        return {
            .type           = type,
            .health         = UINT16_MAX,
            .attack         = UINT16_MAX,
            .hitbox_width   = 13,
            .hitbox_height  = 16,
            .world_pos      = pos,
            .tex_pos        = {pos.x + (SPRITE_SIZE - 13) / 2.0f, pos.y + (SPRITE_SIZE - 16) / 2.0f},
            .delta_pos      = {0.0f, 0.0f},
            .sprite         = &sprites::ORC_WALK,
            .sprite_tick    = 0,
            .sprite_flipped = false
        };
    }
}

constexpr const sprite* get_sprite(enemy_type enemy_type, sprite_type sprite_type) {
    switch (enemy_type) {
    case ORC:
        switch (sprite_type) {
        case WALK:  return &sprites::ORC_WALK;
        case DEATH: return &sprites::ORC_DEATH;
        default: break;
        }
    }

    return nullptr;
}

}