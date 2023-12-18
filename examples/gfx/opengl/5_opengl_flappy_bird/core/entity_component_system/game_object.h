#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <string>

#include "object.h"
#include "transform.h"

namespace game::core {
    class GameObject : public ecs::Object {
        private:
            std::string name;
            Transform transform;

        public:
            GameObject(const std::string& name);
            GameObject(const std::string& name, const Transform& transform);

            Transform& get_transform();
            std::string get_name() const;
            
            void update();

    };
}

#endif
