#ifndef _SPRITE_RENDERER_H_
#define _SPRITE_RENDERER_H_

#include <memory>

#include "../component.h"
#include "../../sprite.h"

namespace game::core::ecs {
    class SpriteRenderer : public Component {
        private:
            shared_ptr<Sprite> sprite;

        public:
            SpriteRenderer();
            SpriteRenderer(const shared_ptr<Sprite>& sprite);
            ~SpriteRenderer();

            const shared_ptr<Sprite>& get_sprite() const;
            void set_sprite(const shared_ptr<Sprite>& sprite);

            void update();
    };
}

#endif
