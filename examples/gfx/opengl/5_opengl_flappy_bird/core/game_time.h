#ifndef _GAME_TIME_H_
#define _GAME_TIME_H_

#include <chrono>

namespace game::core {
    using namespace std::chrono;

    class Time {
        public:
            static const steady_clock::time_point startupTime;
            static double deltaTime;

            static double get_time();
    };
}

#endif
