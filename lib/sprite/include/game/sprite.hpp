#pragma once

#include <cstdint>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GLES3/gl3.h>
#include <EGL/egl.h>
#else
#include <glad/glad.h>
#endif

#include <game/time.hpp>

namespace gm {

constexpr uint8_t SPRITE_SIZE = 41;

constexpr uint8_t SPRITE_RATE = 10;
constexpr uint8_t SPRITE_STEP = TICK_RATE / SPRITE_RATE;

constexpr uint16_t ATLAS_WIDTH  = 8 * SPRITE_SIZE;
constexpr uint16_t ATLAS_HEIGHT = 5 * SPRITE_SIZE;

struct Sprite {
    const uint8_t FRAME_COUNT;
    const uint16_t ATLAS_POS;
};

enum SpriteType {
    WALK,
    DEATH
};

namespace sprites {

constexpr Sprite PLAYER_WALK {
    .FRAME_COUNT  = 8,
    .ATLAS_POS    = ATLAS_HEIGHT - 1 * SPRITE_SIZE
};

constexpr Sprite PLAYER_ATTACK {
    .FRAME_COUNT  = 6,
    .ATLAS_POS    = ATLAS_HEIGHT - 2 * SPRITE_SIZE
};

constexpr Sprite PLAYER_DEATH {
    .FRAME_COUNT  = 4,
    .ATLAS_POS    = ATLAS_HEIGHT - 3 * SPRITE_SIZE
};

constexpr Sprite ORC_WALK {
    .FRAME_COUNT  = 8,
    .ATLAS_POS    = ATLAS_HEIGHT - 4 * SPRITE_SIZE
};

constexpr Sprite ORC_DEATH {
    .FRAME_COUNT  = 4,
    .ATLAS_POS    = ATLAS_HEIGHT - 5 * SPRITE_SIZE
};

}

}
