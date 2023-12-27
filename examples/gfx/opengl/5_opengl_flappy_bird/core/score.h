#ifndef _SCORE_H_
#define _SCORE_H_

namespace game::core::ecs {
    class Score {
        private:
            static int score;
        public:
            static int get_score();
            static void increment();
            static void clear();
    };    
}

#endif
