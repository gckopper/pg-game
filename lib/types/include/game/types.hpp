#pragma once

#include <array>
#include <cstdint>

#include <glad/glad.h>

#include <game/sprite.hpp>
#include <game/utils.hpp>

namespace gm {

struct Coordinate {
    GLfloat x;
    GLfloat y;

    constexpr Coordinate operator+(const Coordinate& other) const {
        return { this->x + other.x, this->y + other.y };
    }

    constexpr Coordinate& operator+=(const Coordinate& other) {
        return *this = *this + other;
    }
};

struct Background {
    Coordinate tex_shift;
};

struct Player {
    uint16_t health = UINT16_MAX;
    uint16_t attack = UINT16_MAX;

    uint8_t hitbox_width  = 12;
    uint8_t hitbox_height = 18;

    uint8_t attack_cooldown = UINT8_MAX;

    Coordinate world_pos = {(WORLD_WIDTH - 12) / 2.0f, (WORLD_HEIGHT - 18) / 2.0f};

    const Sprite* sprite = &sprites::PLAYER_WALK;
    uint8_t sprite_tick  = 0;
    bool sprite_flipped  = false;
};

enum EnemyType {
    ORC
};

struct Enemy {
    EnemyType type;

    uint16_t health;
    uint16_t attack;

    uint8_t hitbox_width;
    uint8_t hitbox_height;

    Coordinate world_pos;
    Coordinate tex_pos;
    Coordinate delta_pos;

    const Sprite* sprite;
    uint8_t sprite_tick;
    bool sprite_flipped;
};

constexpr uint8_t MAX_ENEMIES = 64;

struct Entities {
    Player player;
    
    std::array<Enemy, MAX_ENEMIES> enemies;
    uint8_t enemy_count;

    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLuint texture;

    std::array<GLfloat,  (MAX_ENEMIES + 1) * 24> vbo_data;
    std::array<GLushort, (MAX_ENEMIES + 1) * 6>  ebo_data;

    GLuint shader_program;
};

void setup_entities(Entities& entities);

constexpr Enemy make_enemy(EnemyType type, Coordinate pos) {
    switch (type) {
    case ORC:
        return {
            .type           = type,
            .health         = UINT16_MAX,
            .attack         = UINT16_MAX,
            .hitbox_width   = 13,
            .hitbox_height  = 16,
            .world_pos      = pos,
            .tex_pos        = {pos.x - (SPRITE_SIZE - 13) / 2.0f, pos.y - (SPRITE_SIZE - 16) / 2.0f},
            .delta_pos      = {0.0f, 0.0f},
            .sprite         = &sprites::ORC_WALK,
            .sprite_tick    = 0,
            .sprite_flipped = false };
    }
}

constexpr const Sprite* get_sprite(EnemyType enemy_type, SpriteType sprite_type) {
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
