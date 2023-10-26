#include "texture_loader.h"

namespace game::core {
    std::shared_ptr<GLTexture> TextureLoader::load_texture(const std::string& path) {
        return std::make_shared<GLTexture>(path, GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE);
    }
}