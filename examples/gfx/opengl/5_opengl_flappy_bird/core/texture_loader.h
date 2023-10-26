#ifndef _TEXTURE_LOADER_H_
#define _TEXTURE_LOADER_H_

#include "bebone/bebone.h"

#include <string>
#include <memory>

namespace game::core {
    using namespace bebone::gfx::opengl;
    using namespace bebone::core;

    class TextureLoader : NonCopyable {
        public:
            static std::shared_ptr<GLTexture> load_texture(const std::string& path);
    };
}

#endif
