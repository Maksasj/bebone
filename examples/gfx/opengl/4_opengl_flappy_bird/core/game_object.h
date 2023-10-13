#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "ecs/object.h"
#include "transform.h"

namespace game::core {
    class GameObject : public ecs::Object {
        private:
            Transform transform;

        public:
            GameObject(const Transform& transform);

            const Transform& get_transform() const;
            
            void update();
    };
}

#endif
