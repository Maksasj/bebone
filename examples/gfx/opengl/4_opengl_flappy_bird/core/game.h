#ifndef _GAME_H_
#define _GAME_H_

#include "bebone/bebone.h"
#include "renderer.h"

namespace game::core {
    class Game : private bebone::core::NonCopyable {
        private:
            Renderer renderer;
            OrthographicCamera camera;

        public:
            Game(const unsigned int& width, const unsigned int& height);
            void update();
    };
}

#endif
