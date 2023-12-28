#include "rng.h"

namespace game::core {
    random_device Random::randomDevice;
    mt19937 Random::generator(Random::randomDevice());

    float Random::rand(const float& min, const float& max) {
        uniform_real_distribution<float> distribution(min, max);
        return distribution(generator);
    }
}