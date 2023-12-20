#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "bebone/bebone.h"

namespace game::core {
    using namespace bebone::core;

    class Transform {
        private:
            Vec2f position;
            f32 rotation;
            f32 scale;
        
        public:
            Transform();
            Transform(const Vec2f& position);
            Transform(const Vec2f& position, const f32& rotation, const f32& scale);

            const Vec2f& get_position() const;
            void set_position(const Vec2f& newPosition);

            const f32& get_rotation() const;
            void set_rotation(const f32& newRotation);

            const f32& get_scale() const;
            void set_scale(const f32& newScale);
    };
}

#endif
