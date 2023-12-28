#include "game_time.h"

namespace game::core {
    const steady_clock::time_point Time::startupTime = steady_clock::now();
    double Time::deltaTime = -1;

    double Time::get_time() {
        auto now = steady_clock::now();
        return duration_cast<microseconds>(now - startupTime).count() / 1000000.0;
    }
}