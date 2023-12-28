#include "orthographic_camera.h"

namespace game::core {
    OrthographicCamera::OrthographicCamera(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far) {
        projection = Mat4f::orthographic(right, left, bottom, top, near, far);
    }

    const Mat4f& OrthographicCamera::get_projection_matrix() const {
        return projection;
    }
}