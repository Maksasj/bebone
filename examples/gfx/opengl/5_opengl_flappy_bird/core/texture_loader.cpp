#include "texture_loader.h"

namespace game::core {
    std::string TextureLoader::assets_path;
    std::map<const std::string, std::shared_ptr<GLTexture2D>> TextureLoader::loaded_textures;

    void TextureLoader::load_textures(const std::string& path) {
        TextureLoader::assets_path = path;

        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            auto texture = std::make_shared<GLTexture2D>(entry.path().string());

            std::string file_name = entry.path().stem().string();
            loaded_textures[file_name] = texture;
        }
    }

    std::shared_ptr<GLTexture2D> TextureLoader::get_texture(const std::string& file_name) {
        if (loaded_textures.find(file_name) != loaded_textures.end())
            return loaded_textures[file_name];

        return nullptr;
    }
}