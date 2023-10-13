#ifndef _GAME_H_
#define _GAME_H_

#include "bebone/bebone.h"
#include "renderer.h"

#include <memory>

namespace game::core {
    class Game : private bebone::core::NonCopyable {
        private:
            std::shared_ptr<Renderer> renderer;
            OrthographicCamera camera;

        public:
            Game(const unsigned int& width, const unsigned int& height);
            void update(GLTexture& texture);
    };
}

#endif
