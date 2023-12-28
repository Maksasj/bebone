#include "sprite_renderer.h"

namespace game::core::ecs {
    SpriteRenderer::SpriteRenderer() { }
    SpriteRenderer::SpriteRenderer(const shared_ptr<Sprite>& sprite) : sprite(sprite) { }
    SpriteRenderer::~SpriteRenderer() { sprite = nullptr; }

    const shared_ptr<Sprite>& SpriteRenderer::get_sprite() const {
        return sprite;
    }

    void SpriteRenderer::set_sprite(const shared_ptr<Sprite>& sprite) {
        this->sprite = sprite;
    }

    void SpriteRenderer::enable() {
        if (is_enabled()) {
            return;
        }

        Component::enable();
        // TODO: Add to batch
    }

    void SpriteRenderer::disable() {
        if (!is_enabled()) {
            return;
        }

        Component::disable();
        // TODO: Remove from batch
    }
}