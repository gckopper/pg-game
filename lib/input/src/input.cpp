#include <game/input.hpp>

static gm::Input input;

void gm::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action != GLFW_PRESS && action != GLFW_RELEASE) {
        return;
    }
    const int press = 2 * (action == GLFW_PRESS) - 1;
    switch (key) {
    case GLFW_KEY_W:
    case GLFW_KEY_UP:
        input.movement.y += 1.0 * press;
        break;
    case GLFW_KEY_S:
    case GLFW_KEY_DOWN:
        input.movement.y -= 1.0 * press;
        break;
    case GLFW_KEY_RIGHT:
    case GLFW_KEY_D:
        input.movement.x += 1.0 * press;
        break;
    case GLFW_KEY_A:
    case GLFW_KEY_LEFT:
        input.movement.x -= 1.0 * press;
        break;
    case GLFW_KEY_SPACE:
        input.attack = action == GLFW_PRESS;
        break;
    }
}

gm::Input gm::get_input(Player& player) {
    gm::Input result = input;

    result.movement.x = std::clamp(result.movement.x, -1.0f, 1.0f);
    result.movement.y = std::clamp(result.movement.y, -1.0f, 1.0f);

    if (std::abs(result.movement.x) < 0.1f) {
        result.movement.x = 0.0f;
    }
    if (std::abs(result.movement.y) < 0.1f) {
        result.movement.y = 0.0f;
    }

    if (result.movement.x != 0.0f && result.movement.y != 0.0f) {
        result.movement.x *= 0.7071067811865476f;
        result.movement.y *= 0.7071067811865476f;
    }

    result.movement.x *= player.speed;
    result.movement.y *= player.speed;

    return result;
}
