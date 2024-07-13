#include "transform.h"
namespace bebone::renderer {
    Mat4f calculate_transform_matrix(const Transform& transform) {
        return Mat4f::translation(transform.position) * trait_bryan_angle_yxz(transform.rotation) * Mat4f::scale(1.0f);
    }
}
