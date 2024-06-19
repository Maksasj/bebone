/**
 * @file 
 * matrix.tpp
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _OMNI_TYPES_MATRIX_TPP_
#define _OMNI_TYPES_MATRIX_TPP_

#include "../vector/vector_types.h"
#include "../primitive_types.h"

#include <ostream>
#include <sstream>
#include <cmath>

namespace omni::types {
    /**
     * @brief Type that used as mathematical matrix
     * 
     * @tparam _T type of the matrix
     * @tparam _width width of the matrix
     * @tparam _heigth height of the matrix
    */
    template<typename _T, u32 _width, u32 _heigth>
    struct Matrix {
        /**
         * @brief Raw matrix values
        */
        _T e[_width * _heigth];

        _T& operator()(const size_t& row, const size_t& col) {
            return e[_width * row + col];
        }

        const _T& operator()(const size_t& row, const size_t& col) const {
            return e[_width * row + col];
        }

        /**
         * @brief Method used to get string representation of object instance
         * 
         * @return std::string string representation 
        */
        std::string to_string() const {
            std::stringstream ss;

            for(i32 i = 0; i < _width * _heigth; ++i)
                ss << e[i] << " ";
            
            return ss.str();
        }
    };

    /**
     * @brief Puts string representation of the object to the out stream
     * 
     * @param os - reference to the out stream
     * @param mat - reference to the object instance
     * 
     * @return std::ostream& reference to the stream instance 
    */
    template<typename _T, u32 _width, u32 _heigth>
    std::ostream& operator<<(std::ostream& os, const Matrix<_T, _width, _heigth>& mat) {
        for(i32 i = 0; i < _width * _heigth; ++i)
            os << mat.e[i] << " ";

        return os;
    } 

    /**
     * @brief Constructs object from it string representation
     * 
     * @param os - reference to the in stream
     * @param mat - reference to the object instance
     * 
     * @return std::istream& reference to the stream instance 
    */
    template<typename _T, u32 _width, u32 _heigth>
    std::istream& operator>>(std::istream& os, const Matrix<_T, _width, _heigth>& mat) {
        for(i32 i = 0; i < _width * _heigth; ++i)
            os >> mat.e[i];

        return os;
    }
}

#endif
