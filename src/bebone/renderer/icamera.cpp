#include "icamera.h"

namespace bebone::renderer {
    ICamera::ICamera() : cam_position(Vec3f::zero), cam_direction(Vec3f::forward) {

    }

    void ICamera::apply_position(const Vec3f& position) {
        cam_position += position;
    }

    void ICamera::apply_direction(const Vec3f& direction) {
        cam_direction += direction;
    }

    void ICamera::set_position(const Vec3f& position) {
        this->cam_position = position;
    }

    void ICamera::set_direction(const Vec3f& direction) {
        this->cam_direction = direction;
    }

    const Vec3f& ICamera::get_position() const {
        return cam_position;
    }

    const Vec3f& ICamera::get_direction() const {
        return cam_direction;
    }
}
