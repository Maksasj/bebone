#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <string>
#include <memory>

#include "object.h"
#include "transform.h"

namespace game::core::ecs {
    using namespace std;

    class GameObject : public ecs::Object {
        private:
            string name;
            shared_ptr<Transform> transform;

        public:
            GameObject(const string& name);
            GameObject(const string& name, const Vec3f& position);

            shared_ptr<Transform>& get_transform();
            string get_name() const;
            
            void update();

    };
}

#endif
