#pragma once

#include <array>
#include <cstdint>
#include <glad/glad.h>

namespace gm {
    constexpr uint64_t MAX_MOBS = 128;
    struct coord {
        float x = 0, y = 0;
    };
    struct vertex {
        coord pos_diff;
        coord pos;
        coord tex;
    };
    struct background {
        coord shift;
    };
    struct player {
        int health = 100;
        int damage = 69;
    };
    struct mob {
        coord pos;
        int health;
        int damage;
    };
    struct game {
        background bg;
        player player;
        std::array<mob, MAX_MOBS> mobs;
        int mobs_count = 0;
        unsigned int vbo;
    };
}
