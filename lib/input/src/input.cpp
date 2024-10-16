#include <algorithm>

#include <game/input.hpp>

static gm::Input input;

void gm::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action != GLFW_PRESS && action != GLFW_RELEASE) {
        return;
    }
    const int press = 2 * (action == GLFW_PRESS) - 1;
    input.is_gamepad = false;
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
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;
    }
}

gm::Input gm::get_input(Player& player) {
    constexpr auto getGamepadInput = []() -> void {
        if (!glfwJoystickIsGamepad(GLFW_JOYSTICK_1)) {
            return;
        }
        GLFWgamepadstate state;
        if (!glfwGetGamepadState(GLFW_JOYSTICK_1, &state)) {
            return;
        }
        input.is_gamepad |= state.buttons[GLFW_GAMEPAD_BUTTON_A];
        if (!input.is_gamepad) {
            return;
        }
        input.attack = state.buttons[GLFW_GAMEPAD_BUTTON_A];
        input.movement.x = state.axes[GLFW_GAMEPAD_AXIS_LEFT_X];
        input.movement.y = -state.axes[GLFW_GAMEPAD_AXIS_LEFT_Y];
        if (std::abs(input.movement.x) < 0.1) input.movement.x = 0.f;
        if (std::abs(input.movement.y) < 0.1) input.movement.y = 0.f;
    };

    getGamepadInput();
    gm::Input result = input;

    result.movement.x = std::clamp(result.movement.x, -1.0f, 1.0f);
    result.movement.y = std::clamp(result.movement.y, -1.0f, 1.0f);

    if (!input.is_gamepad && result.movement.x != 0.0f && result.movement.y != 0.0f) {
        result.movement.x *= 0.7071067811865476f;
        result.movement.y *= 0.7071067811865476f;
    }

    result.movement.x *= player.speed;
    result.movement.y *= player.speed;

    return result;
}
