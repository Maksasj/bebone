#include "texture_loader.h"

namespace game::core {
    std::string TextureLoader::assetsPath;
    std::map<const std::string, std::shared_ptr<GLTexture2D>> TextureLoader::loadedTextures;

    void TextureLoader::load_textures(const std::string& assetsPath) {
        TextureLoader::assetsPath = assetsPath;

        for (const auto& entry : std::filesystem::directory_iterator(assetsPath)) {
            auto texture = std::make_shared<GLTexture2D>(entry.path().string());

            std::string fileName = entry.path().stem().string();
            loadedTextures[fileName] = texture;
        }
    }

    std::shared_ptr<GLTexture2D> TextureLoader::get_texture(const std::string& fileName) {
        if (loadedTextures.find(fileName) != loadedTextures.end())
            return loadedTextures[fileName];

        return nullptr;
    }
}