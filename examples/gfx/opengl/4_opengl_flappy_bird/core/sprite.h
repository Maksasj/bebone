#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "bebone/bebone.h"
#include <memory>

using namespace bebone::gfx::opengl;

namespace game::core {
    class Sprite {
        private:
            std::shared_ptr<GLTexture> texture;
        public:
            Sprite();
            Sprite(std::shared_ptr<GLTexture>& texture);

            const std::shared_ptr<GLTexture>& get_texture() const;
            void set_texture(std::shared_ptr<GLTexture>& texture);
    };
}

#endif
