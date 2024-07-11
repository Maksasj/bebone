#ifndef _BEBONE_CORE_TYPES_MATRIX_TYPES_H_
#define _BEBONE_CORE_TYPES_MATRIX_TYPES_H_

#include "matrix.tpp"

#include "matrix_2x2.h"
#include "matrix_3x3.h"
#include "matrix_4x4.tpp"

namespace bebone::core {
    using Matrix2x2f = Matrix<f32, 2, 2>;
    using Mat2f = Matrix2x2f;

    using Matrix3x3f = Matrix<f32, 3, 3>;
    using Mat3f = Matrix3x3f;

    using Matrix4x4f = Matrix<f32, 4, 4>;
    using Mat4f = Matrix4x4f;
}

#endif
