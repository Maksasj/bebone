#ifndef _TEXTURE_LOADER_H_
#define _TEXTURE_LOADER_H_

#include "bebone/bebone.h"

#include <filesystem>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <map>

namespace game::core {
    using namespace bebone::gfx::opengl;
    using namespace bebone::core;

    class TextureLoader : private NonCopyable {
        private:
            static std::map<const std::string, std::shared_ptr<GLTexture>> loadedTextures;
            static std::string assetsPath;

        public:
            static void load_textures(const std::string& assetsPath);
            static std::shared_ptr<GLTexture> get_texture(const std::string& fileName);
    };
}

#endif
