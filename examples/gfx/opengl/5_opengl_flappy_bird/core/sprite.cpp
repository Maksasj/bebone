#include "sprite.h"
#include "texture_loader.h"

namespace game::core {
    using namespace std;

    Sprite::Sprite() : texture(nullptr) {}

    Sprite::Sprite(const std::string& textureName) {
        set_texture(textureName);
    }

    const shared_ptr<GLTexture>& Sprite::get_texture() const {
        return texture;
    }

    void Sprite::set_texture(const std::string& textureName) {
        texture = TextureLoader::get_texture(textureName);
    }
}