#ifndef _TIMESTAMP_H
#define _TIMESTAMP_H

#include <chrono>

namespace bebone::core {
    using namespace std::chrono;

    class Time {
        private:
            static double delta_time;

    public:
            static const steady_clock::time_point startup_time;

            static double get_delta_time();
            static double get_seconds_elapsed();

            static void set_delta_time(const double& time);
    };

    struct Timestamp {
        public:
            double time;

            Timestamp();

            double operator-(const Timestamp& timestamp) const;
            double operator+(const Timestamp& timestamp) const;
    };
}

#endif
