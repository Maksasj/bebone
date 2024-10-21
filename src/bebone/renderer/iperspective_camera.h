#ifndef _BEBONE_RENDERER_IPERSPECTIVE_CAMERA_H_
#define _BEBONE_RENDERER_IPERSPECTIVE_CAMERA_H_

#include "icamera.h"

namespace bebone::renderer {
    class IPerspectiveCamera : public ICamera {
        protected:
            f32 fov;

            f32 near_plane;
            f32 far_plane;

        public:
            IPerspectiveCamera(const f32& fov, const f32& near_plane, const f32& far_plane);

            Mat4f calculate_matrix(const f32& aspect_ratio) const override;

            const f32& get_fov() const;
            const f32& get_near_plane() const;
            const f32& get_far_plane() const;

            void set_fov(const f32& new_fov);
            void set_near_plane(const f32& new_near_plane);
            void set_far_plane(const f32& new_far_plane);
    };
}

#endif
