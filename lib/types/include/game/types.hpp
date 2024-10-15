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

    constexpr Coordinate operator-(const Coordinate& other) const {
        return { this->x - other.x, this->y - other.y };
    }

    constexpr Coordinate& operator-=(const Coordinate& other) {
        return *this = *this - other;
    }

    constexpr Coordinate operator-() const {
        return { -this->x, -this->y };
    }

    constexpr Coordinate operator*(const Coordinate& other) const {
        return { this->x * other.x, this->y * other.y };
    }

    constexpr Coordinate& operator*=(const Coordinate& other) {
        return *this = *this * other;
    }

    constexpr bool operator==(const Coordinate& other) const {
        return this->x == other.x && this->y == other.y;
    }
};

struct Background {
    Coordinate tex_shift;

    GLuint vao;
    GLuint vbo;

    GLuint u_time_delta;

    GLuint texture;

    GLfloat texture_width = 100.0f;
    GLfloat texture_height = 100.0f;

    std::array<GLfloat, 24> vbo_data;

    GLuint shader_program;
};

void setup_background(Background& background);

struct Hitbox {
    Coordinate pos;

    uint8_t width;
    uint8_t height;
};

constexpr int16_t PLAYER_MAX_HEALTH = 100;

struct Player {
    int16_t health = PLAYER_MAX_HEALTH;
    int16_t attack = INT16_MAX;
    GLfloat speed  = 3.0f;

    Hitbox hitbox = {
        .pos    = {(WORLD_WIDTH - 12) / 2.0f, (WORLD_HEIGHT - 18) / 2.0f},
        .width  = 12,
        .height = 18
    };

    bool attacking = false;

    const Sprite* sprite = &sprites::PLAYER_WALK;
    uint8_t sprite_tick  = 0;
    bool sprite_flipped  = false;
};

struct Healthbar {
    GLfloat width  = 80.0f;
    GLfloat height = 7.0f;
    GLfloat offset = 16.0f;

    GLuint vao;

    GLuint shader_program;
    GLuint texture;
    GLint  u_health_percentage;
};

void setup_healthbar(Healthbar& healthbar);

enum EnemyType {
    ORC
};

struct Enemy {
    EnemyType type;

    int16_t health;
    int16_t attack;

    GLfloat speed;

    Hitbox hitbox;

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
    GLuint u_time_delta;

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
            .health         = INT16_MAX,
            .attack         = 1,
            .speed          = 1.5f,
            .hitbox         = {
                .pos    = pos,
                .width  = 13,
                .height = 16
            },
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
