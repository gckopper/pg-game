#include <game/time.hpp>

int main() {
    gm::duration delta_time;
    gm::time_point time, last_tick_time{gm::get_time()};

    while (true) {
        time = gm::get_time();
        delta_time = time - last_tick_time;

        // render(delta_time.count());

        if (delta_time >= gm::TICK_STEP) {
            // update_state();

            last_tick_time = time;
        }
    }

    return 0;
}