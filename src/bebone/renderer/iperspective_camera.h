#ifndef _BEBONE_RENDERER_IPERSPECTIVE_CAMERA_H_
#define _BEBONE_RENDERER_IPERSPECTIVE_CAMERA_H_

#include "icamera.h"

namespace bebone::renderer {
    class IPerspectiveCamera : public ICamera {
        public:
            IPerspectiveCamera();

            Mat4f calculate_matrix(const f32& aspect_ratio) const override;
    };
}

#endif
