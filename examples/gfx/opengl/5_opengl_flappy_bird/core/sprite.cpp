#include "sprite.h"
#include "texture_loader.h"

namespace game::core {
    using namespace std;

    Sprite::Sprite() : texture(nullptr), pixelsPerUnit(32) {}

    Sprite::Sprite(const std::string& textureName, const unsigned int& pixelsPerUnit) : pixelsPerUnit(pixelsPerUnit) {
        set_texture(textureName);
    }

    const shared_ptr<GLTexture>& Sprite::get_texture() const {
        return texture;
    }

    void Sprite::set_texture(const std::string& textureName) {
        texture = TextureLoader::get_texture(textureName);
    }

    int Sprite::get_height() const {
        return texture->get_height();
    }

    int Sprite::get_width() const {
        return texture->get_width();
    }

    unsigned int Sprite::get_pixels_per_unit() const {
        return pixelsPerUnit;
    }
}