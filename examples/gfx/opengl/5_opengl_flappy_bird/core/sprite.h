#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "bebone/bebone.h"
#include <memory>
#include <string>

using namespace bebone::gfx::opengl;

namespace game::core {
    using namespace std;

    class Sprite : private NonCopyable {
        private:
            shared_ptr<GLTexture> texture;
        public:
            Sprite();
            Sprite(const std::string& textureName);

            const shared_ptr<GLTexture>& get_texture() const;
            void set_texture(const std::string& textureName);
    };
}

#endif
