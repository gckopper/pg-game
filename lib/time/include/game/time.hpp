#pragma once

#include <chrono>
#include <cstdint>
#include <ratio>
#include <type_traits>

namespace gm {

typedef std::conditional_t<
    std::chrono::high_resolution_clock::is_steady,
    std::chrono::high_resolution_clock,
    std::chrono::steady_clock
> clock;
typedef uint64_t time_t;
typedef std::chrono::duration<time_t, std::micro> duration;
typedef std::chrono::time_point<clock, duration> time_point;

inline time_point get_time() {
    return std::chrono::time_point_cast<duration>(clock::now());
}

constexpr const uint8_t  TICK_RATE = 20;
constexpr const duration TICK_STEP = duration{std::chrono::seconds{1}} / TICK_RATE;

}