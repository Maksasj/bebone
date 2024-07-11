#ifndef _BEBONE_CORE_TYPES_MATRIX_TPP_
#define _BEBONE_CORE_TYPES_MATRIX_TPP_

#include "../vector/vector_types.h"
#include "../primitive_types.h"

#include <ostream>
#include <sstream>
#include <cmath>

namespace bebone::core {
    /**
     * @brief Type that used as mathematical matrix
     * 
     * @tparam T type of the matrix
     * @tparam width width of the matrix
     * @tparam height height of the matrix
    */
    template<typename T, u32 width, u32 height>
    struct Matrix {
        /**
         * @brief Raw matrix values
        */
        //T e[width * height];
        T e[width][height];

        T& operator()(const size_t& row, const size_t& col) {
            return e[col][row];
        }

        const T& operator()(const size_t& row, const size_t& col) const {
            return e[col][row];
        }

        /**
         * @brief Method used to get string representation of object instance
         * 
         * @return std::string string representation 
        */
         std::string to_string() const {
             std::stringstream ss;

             for (i32 i = 0; i < width; ++i) {
                 for (i32 j = 0; j < height; ++j) {
                     ss << e[i][j] << " ";
                 }
                 ss << std::endl;
             }

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
     template<typename T, u32 width, u32 height>
     std::ostream& operator<<(std::ostream& os, const Matrix<T, width, height>& mat) {
         for (i32 i = 0; i < width; ++i) {
             for (i32 j = 0; j < height; ++j) {
                 os << mat.e[i][j] << " ";
             }
         }

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
     template<typename T, u32 width, u32 height>
     std::istream& operator>>(std::istream& os, const Matrix<T, width, height>& mat) {
        for (i32 i = 0; i < width; ++i) {
            for (i32 j = 0; j < height; ++j) {
                os >> mat.e[i][j];
            }
        }

         return os;
     }
}

#endif
