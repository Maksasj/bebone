#include "timestamp.h"

namespace bebone::core {
    const steady_clock::time_point Time::startup_time = steady_clock::now();
    double Time::delta_time = 1.0f / 60;

    void Time::set_delta_time(const double& time) {
        if (time <= 0) {
            return;
        }

        delta_time = time;
    }

    double Time::get_delta_time() {
        return delta_time;
    }

    double Time::get_seconds_elapsed() {
        auto now = steady_clock::now();
        return duration_cast<microseconds>(now - startup_time).count() / 1000000.0;
    }
}