#include "iperspective_camera.h"

namespace bebone::renderer {
    IPerspectiveCamera::IPerspectiveCamera() : ICamera() {

    }

    Mat4f IPerspectiveCamera::calculate_matrix(const f32& aspect_ratio) const {
        const auto view = Mat4f::view(Vec3f(0.0f, 0.0f, 5.0f), Vec3f::back, Vec3f::down);
        const auto proj = Mat4f::perspective(1.0472, aspect_ratio, 0.1f, 100.0f);

        return view * proj;
    }
}
