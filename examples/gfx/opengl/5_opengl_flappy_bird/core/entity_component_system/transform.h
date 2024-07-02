#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "bebone/bebone.h"

namespace game::core::ecs {
    using namespace bebone::core;

    class Transform {
        private:
            Vec3f position;
            f32 rotation;
            f32 scale;
        
        public:
            Transform();
            Transform(const Vec3f& position);
            Transform(const Vec3f& position, const f32& rotation, const f32& scale);

            const Vec3f& get_position() const;
            void set_position(const Vec3f& new_position);

            const f32& get_rotation() const;
            void set_rotation(const f32& new_rotation);

            const f32& get_scale() const;
            void set_scale(const f32& new_scale);

            void move(const Vec3f& v);
    };
}

#endif
