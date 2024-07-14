#include "iperspective_camera.h"

namespace bebone::renderer {
    IPerspectiveCamera::IPerspectiveCamera() : ICamera() {

    }

    Mat4f IPerspectiveCamera::calculate_matrix(const f32& aspect_ratio) const {
        auto proj = Mat4f::perspective(1.0472, aspect_ratio, 0.1f, 100.0f);

        const auto direction = get_direction();
        const auto position = get_position();

        return Mat4f::look_at(position, position + direction, Vec3f::up) * proj;
    }
}
