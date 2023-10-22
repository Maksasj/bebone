#include "sprite.h"

namespace game::core {
    using namespace std;

    Sprite::Sprite() : texture(nullptr) {}
    Sprite::Sprite(shared_ptr<GLTexture>& texture) : texture(texture) {}

    const shared_ptr<GLTexture>& Sprite::get_texture() const {
        return texture;
    }

    void Sprite::set_texture(shared_ptr<GLTexture>& texture) {
        this->texture = texture;
    }
}