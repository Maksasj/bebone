#ifndef _SPRITE_RENDERER_H_
#define _SPRITE_RENDERER_H_

#include "../i_component.h"
#include "../../sprite.h"

namespace game::core::ecs {
    class SpriteRenderer : public IComponent {
        private:
            Sprite sprite;

        public:
            SpriteRenderer(Sprite& sprite);
    };
}

#endif
