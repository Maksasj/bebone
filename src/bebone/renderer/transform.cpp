#include "transform.h"
namespace bebone::renderer {
    Mat4f Transform::final_matrix() const {
        return Mat4f::translation(position) * trait_bryan_angle_yxz(rotation) * Mat4f::scale(1.0f);
    }
}
