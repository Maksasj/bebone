#ifndef _GAME_H_
#define _GAME_H_

#include <memory>

#include "bebone/bebone.h"
#include "batch.h"
#include "sprite.h"

namespace game::core {
    using namespace std;

    class Game : private bebone::core::NonCopyable {
        private:
            shared_ptr<Batch> batch;
            shared_ptr<OrthographicCamera> camera;

        public:
            Game(const unsigned int& width, const unsigned int& height);
            void update();
    };
}

#endif
