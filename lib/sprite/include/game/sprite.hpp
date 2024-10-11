#pragma once

#include <cstdint>

#include <glad/glad.h>

#include <game/time.hpp>

namespace gm {

constexpr uint8_t SPRITE_SIZE = 41;

constexpr uint8_t SPRITE_RATE = 10;
constexpr uint8_t SPRITE_STEP = TICK_RATE / SPRITE_RATE;

constexpr uint16_t ATLAS_WIDTH  = 8 * SPRITE_SIZE;
constexpr uint16_t ATLAS_HEIGHT = 5 * SPRITE_SIZE;

struct sprite {
    const uint8_t FRAME_COUNT;
    const uint16_t ATLAS_POS;
};

enum sprite_type {
    WALK,
    DEATH
};

namespace sprites {

constexpr sprite PLAYER_WALK {
    .FRAME_COUNT  = 8,
    .ATLAS_POS    = ATLAS_HEIGHT - 1 * SPRITE_SIZE
};

constexpr sprite PLAYER_ATTACK {
    .FRAME_COUNT  = 6,
    .ATLAS_POS    = ATLAS_HEIGHT - 2 * SPRITE_SIZE
};

constexpr sprite PLAYER_DEATH {
    .FRAME_COUNT  = 4,
    .ATLAS_POS    = ATLAS_HEIGHT - 3 * SPRITE_SIZE
};

constexpr sprite ORC_WALK {
    .FRAME_COUNT  = 8,
    .ATLAS_POS    = ATLAS_HEIGHT - 4 * SPRITE_SIZE
};

constexpr sprite ORC_DEATH {
    .FRAME_COUNT  = 4,
    .ATLAS_POS    = ATLAS_HEIGHT - 5 * SPRITE_SIZE
};

}

}
