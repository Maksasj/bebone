/**
 * @file 
 * matrix_types.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _OMNI_TYPES_MATRIX_TYPES_H_
#define _OMNI_TYPES_MATRIX_TYPES_H_

#include "../primitive_types.h"

#include "matrix.tpp"

#include "matrix_2x2.tpp"
#include "matrix_4x4.tpp"

namespace bebone::core {
    using Matrix2x2f = Matrix<f32, 2, 2>;
    using Mat2f = Matrix2x2f;

    using Matrix4x4f = Matrix<f32, 4, 4>;
    using Mat4f = Matrix4x4f;
}

#endif
