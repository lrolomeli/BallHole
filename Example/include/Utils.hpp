#pragma once

#include <SDL2/SDL.h>
#include <cstdint>

namespace utils {
    inline float stime_s() {
        uint32_t ticks = SDL_GetTicks(); // Get milliseconds since SDL initialization
        float seconds = ticks / 1000.0; // Convert to seconds (using floating-point division)

        // std::cout << "Milliseconds: " << ticks << "\n";
        // std::cout << "Seconds: " << seconds << "\n";
        return seconds;
    }
}