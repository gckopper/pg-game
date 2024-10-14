#include <glad/glad.h>

#include <game/input.hpp>
#include <game/types.hpp>

namespace gm {

void update_vbo(Entities& entities);

void update_background(Background& background, Input& input);

template<class T, class U>
constexpr bool colliding(T first, U second) {
    return first.world_pos.x < second.world_pos.x  + second.hitbox_width  &&
           first.world_pos.x + first.hitbox_width  > second.world_pos.x   &&
           first.world_pos.y < second.world_pos.y  + second.hitbox_height &&
           first.world_pos.y + first.hitbox_height > second.world_pos.y;
}

}
