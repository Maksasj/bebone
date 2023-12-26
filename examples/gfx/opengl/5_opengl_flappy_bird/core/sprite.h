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
            unsigned int pixelsPerUnit;

            float unitWidth;
            float unitHeight;
        public:
            Sprite();
            Sprite(const std::string& textureName, const unsigned int& pixelsPerUnit);

            const shared_ptr<GLTexture>& get_texture() const;
            void set_texture(const std::string& textureName);
            
            int get_height() const;
            int get_width() const;

            unsigned int get_pixels_per_unit() const;

            float get_unit_width() const;
            float get_unit_height() const;
    };
}

#endif
