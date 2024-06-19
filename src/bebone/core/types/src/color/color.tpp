/**
 * @file
 * color.tpp
 *
 * @author
 * Maksim Jaroslavcevas radioboos@gmail.com
 *
 * @copyright
 * see LICENSE.md file
*/

#ifndef _OMNI_TYPES_COLOR_TYPE_H_
#define _OMNI_TYPES_COLOR_TYPE_H_

#include <stdlib.h>
#include "../primitive_types.h"
#include "../vector/vector_types.h"

#ifndef OMNI_TYPES_RAND
    #define OMNI_TYPES_RAND rand()
#endif

#include "color_format.h"

#ifdef OMNI_GLAD_INTEGRATION
    #include <glad/glad.h>
#endif

namespace omni::types {
    template<ColorFormat _Format>
    struct Color {

    };
}

#endif
