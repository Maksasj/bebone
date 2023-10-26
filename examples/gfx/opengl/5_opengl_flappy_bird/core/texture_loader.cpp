#include "texture_loader.h"

namespace game::core {
    void TextureLoader::load_textures(const std::string& assetsDirectory) {
        // assetsPath = assetsDirectory;

        // for (const auto& entry : std::filesystem::directory_iterator(assetsDirectory)) {
        //     std::shared_ptr<GLTexture> texture = std::make_shared<GLTexture>(entry.path().c_str(), GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE);

        //     std::string fileName = entry.path().stem().generic_string();
        //     loadedTextures[fileName] = texture;
        // }
    }
}