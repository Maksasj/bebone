#include "iperspective_camera.h"

namespace bebone::renderer {
    IPerspectiveCamera::IPerspectiveCamera() : ICamera() {

    }

    Mat4f IPerspectiveCamera::calculate_matrix(const f32& aspect_ratio) const {
        const auto view = Mat4f::view(get_position(), Vec3f::back, Vec3f::down);
        const auto proj = Mat4f::perspective(1.0472, aspect_ratio, 0.1f, 100.0f);

        return view * proj;
    }
}
