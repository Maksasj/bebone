#include "sprite.h"

namespace game::core {
    Sprite::Sprite() : texture(nullptr) {}
    Sprite::Sprite(std::shared_ptr<GLTexture>& texture) : texture(texture) {}

    const std::shared_ptr<GLTexture>& Sprite::get_texture() const {
        return texture;
    }

    void Sprite::set_texture(std::shared_ptr<GLTexture>& texture) {
        this->texture = texture;
    }
}