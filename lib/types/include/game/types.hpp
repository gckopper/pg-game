#pragma once

#include <array>
#include <cstdint>
#include <glad/glad.h>

namespace gm {
    constexpr uint64_t MAX_MOBS = 128;
    constexpr uint64_t HEIGHT = 720;
    constexpr uint64_t WIDTH = 1280;
    struct coord {
        float x = 0, y = 0;
    };
    struct vertex {
        coord pos_diff;
        coord pos;
        coord tex;
    };
    constexpr uint64_t VERT_SIZE = sizeof(vertex);
    constexpr uint64_t VERT_SIZE_FLOATS = sizeof(vertex)/sizeof(float);
    struct render_unit {
        uint32_t vao;
        uint32_t vbo;
        uint32_t tex;
        uint32_t shader;
        int32_t  u_time;
        int32_t  u_tex;
    };
    struct background {
        coord shift;
        render_unit render;
    };
    struct player {
        uint32_t health = 100;
        uint32_t damage = 69;
    };
    struct mob {
        coord pos;
        uint32_t health;
        uint32_t damage;
    };
    struct game {
        background bg;
        player p;
        std::array<mob, MAX_MOBS> mobs;
        uint32_t mobs_count = 0;
        render_unit entity_render;
    };
}
