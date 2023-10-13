#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "bebone/bebone.h"
using namespace bebone::core;

namespace game::core {
    class Transform {
        private:
            Vec3f position;
            Vec3f rotation;
            f32 scale;
        
        public:
            Transform();
            Transform(const Vec3f& position, const Vec3f& rotation, const f32& scale);

            const Vec3f& get_position() const;
            void set_position(const Vec3f& newPosition);

            const Vec3f& get_rotation() const;
            void set_rotation(const Vec3f& newRotation);

            const f32& get_scale() const;
            void set_scale(const f32& newScale);
    };
}

#endif
