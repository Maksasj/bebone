#ifndef _TIMESTAMP_H
#define _TIMESTAMP_H

#include <chrono>

namespace bebone::core {
    using namespace std::chrono;

    class Time {
    private:
        static double delta_time;

        static void set_delta_time(const double& time);

    public:
        static const steady_clock::time_point startup_time;

        static double get_delta_time();
        static double get_seconds_elapsed();
    };
}

#endif
