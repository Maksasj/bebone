#ifndef _RNG_H_
#define _RNG_H_

#include <random>

#include "bebone/bebone.h"

namespace game::core {
    using namespace std;

    class Random : private bebone::core::NonCopyable {
        private:
            static random_device randomDevice;
            static mt19937 generator;

        public:
            static float rand(const float& min, const float& max);
    };
}

#endif
