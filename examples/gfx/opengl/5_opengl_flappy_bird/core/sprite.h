#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "bebone/bebone.h"
#include <memory>

using namespace bebone::gfx::opengl;

namespace game::core {
    using namespace std;

    class Sprite {
        private:
            shared_ptr<GLTexture> texture;
        public:
            Sprite();
            Sprite(shared_ptr<GLTexture>& texture);

            const shared_ptr<GLTexture>& get_texture() const;
            void set_texture(shared_ptr<GLTexture>& texture);
    };
}

#endif
