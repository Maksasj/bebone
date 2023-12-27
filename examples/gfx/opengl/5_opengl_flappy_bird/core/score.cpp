#include "score.h"

namespace game::core::ecs {
    int Score::score = 0;

    int Score::get_score() {
        return score;
    }

    void Score::increment() {
        ++score;
    }

    void Score::clear() {
        score = 0;
    }
}