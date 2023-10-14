#ifndef _GAME_H_
#define _GAME_H_

#include <memory>

#include "bebone/bebone.h"
#include "renderer.h"

namespace game::core {
    using namespace std;

    class Game : private bebone::core::NonCopyable {
        private:
            shared_ptr<Renderer> renderer;
            shared_ptr<OrthographicCamera> camera;

        public:
            Game(const unsigned int& width, const unsigned int& height);
            void update(Sprite& texture);
    };
}

#endif
