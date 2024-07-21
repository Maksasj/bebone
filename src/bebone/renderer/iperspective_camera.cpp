#include "iperspective_camera.h"

namespace bebone::renderer {
    IPerspectiveCamera::IPerspectiveCamera(
        const f32& fov,
        const f32& near_plane,
        const f32& far_plane
    ) : ICamera(), fov(fov), near_plane(near_plane), far_plane(far_plane) {

    }

    Mat4f IPerspectiveCamera::calculate_matrix(const f32& aspect_ratio) const {
        auto proj = Mat4f::perspective(fov, aspect_ratio, near_plane, far_plane);

        const auto direction = get_direction();
        const auto position = get_position();

        return proj * Mat4f::look_at(position, position + direction, Vec3f::up);
    }

    const f32& IPerspectiveCamera::get_fov() const {
        return fov;
    }

    const f32& IPerspectiveCamera::get_near_plane() const {
        return near_plane;
    }

    const f32& IPerspectiveCamera::get_far_plane() const {
        return far_plane;
    }

    void IPerspectiveCamera::set_fov(const f32& new_fov) {
        fov = new_fov;
    }

    void IPerspectiveCamera::set_near_plane(const f32& new_near_plane) {
        near_plane = new_near_plane;
    }

    void IPerspectiveCamera::set_far_plane(const f32& new_far_plane) {
        far_plane = new_far_plane;
    }
}
