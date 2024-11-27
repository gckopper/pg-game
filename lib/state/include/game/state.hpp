#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#include <GLES3/gl3.h>
#else
#include <glad/glad.h>
#endif

#include <game/input.hpp>
#include <game/types.hpp>
#include <random>

namespace gm {

constexpr GLfloat SPAWN_OFFSET_X = 0.05f * WORLD_WIDTH;
constexpr GLfloat SPAWN_OFFSET_Y = 0.05f * WORLD_HEIGHT;

constexpr GLfloat DESPAWN_DISTANCE_X = 0.75f * WORLD_WIDTH;
constexpr GLfloat DESPAWN_DISTANCE_Y = 0.75f * WORLD_HEIGHT;

void move_enemies(Entities& entities, Coordinate& player_movement);

void update_vbo(Entities& entities);

void player_attack(Entities& entities);

void enemy_attack(Entities& entities, Healthbar& healthbar);

void update_background(Background& background, Input& input);

void spawn_enemy(Entities& entities, std::mt19937& gen);

void update_sprites(Entities& entities, Input& input);

void add_text(const std::string text, const Coordinate pos, const float size, Font& font);

void clear_text(Font& font);

constexpr bool colliding(const Hitbox& lhs, const Hitbox& rhs) {
    return lhs.pos.x < rhs.pos.x  + rhs.width  &&
           lhs.pos.x + lhs.width  > rhs.pos.x  &&
           lhs.pos.y < rhs.pos.y  + rhs.height &&
           lhs.pos.y + lhs.height > rhs.pos.y;
}

}
