#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include "object.h"
#include "transform.h"

namespace game::core {
    class GameObject : public ecs::Object {
        private:
            Transform transform;

        public:
            GameObject();
            GameObject(const Transform& transform);

            Transform& get_transform();
            
            void update();
    };
}

#endif
