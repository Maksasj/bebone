#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "object.h"
#include "transform.h"

namespace game::core {
    class GameObject : public Object {
        private:
            Transform transform;

        public:
            GameObject();
            GameObject(const Vec2f& position);

            const Transform& get_transform() const;
            
            void update();
    };
}

#endif
