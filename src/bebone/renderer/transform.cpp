#include "transform.h"
namespace bebone::renderer {
    Mat4f calculate_transform_matrix(const Transform& transform) {
        return Mat4f::translation(transform.position) * Mat4f::scale(1.0f);
    }
}
