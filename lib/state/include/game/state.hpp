#include <glad/glad.h>

#include <game/input.hpp>
#include <game/types.hpp>

namespace gm {

void move_enemies(Entities& entities, Coordinate& player_movement);

void update_vbo(Entities& entities);

void update_background(Background& background, Input& input);

void update_sprites(Entities& entities, Input& input);

constexpr bool colliding(Hitbox& lhs, Hitbox& rhs) {
    return lhs.pos.x < rhs.pos.x  + rhs.width  &&
           lhs.pos.x + lhs.width  > rhs.pos.x  &&
           lhs.pos.y < rhs.pos.y  + rhs.height &&
           lhs.pos.y + lhs.height > rhs.pos.y;
}

}
