#ifndef _ORTHOGRAPHIC_CAMERA_H_
#define _ORTHOGRAPHIC_CAMERA_H_

#include "bebone/bebone.h"

using namespace bebone::core;

namespace game::core {
    class OrthographicCamera {
        private:
            Mat4f projection;

        public:
            OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far);

            const Mat4f& get_projection_matrix() const;
    };
}

#endif
