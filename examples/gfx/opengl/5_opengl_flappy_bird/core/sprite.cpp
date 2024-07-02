#include "sprite.h"
#include "texture_loader.h"

namespace game::core {
    using namespace std;

    Sprite::Sprite() : texture(nullptr), pixels_per_unit(32) {}

    Sprite::Sprite(const std::string& texture_name, const unsigned int& pixels_per_unit) : pixels_per_unit(pixels_per_unit) {
        set_texture(texture_name);

        unit_width = get_width() / (float)pixels_per_unit;
        unit_height = get_height() / (float)pixels_per_unit;
    }

    const shared_ptr<GLTexture2D>& Sprite::get_texture() const {
        return texture;
    }

    void Sprite::set_texture(const std::string& texture_name) {
        texture = TextureLoader::get_texture(texture_name);
    }

    int Sprite::get_height() const {
        return texture->get_height();
    }

    int Sprite::get_width() const {
        return texture->get_width();
    }

    unsigned int Sprite::get_pixels_per_unit() const {
        return pixels_per_unit;
    }

    float Sprite::get_unit_width() const {
        return unit_width;
    }

    float Sprite::get_unit_height() const {
        return unit_height;
    }
}