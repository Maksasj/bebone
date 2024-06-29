#ifndef _BEBONE_CORE_TYPES_COLOR_TYPE_H_
#define _BEBONE_CORE_TYPES_COLOR_TYPE_H_

#include <stdlib.h>
#include "../primitive_types.h"
#include "../vector/vector_types.h"

#ifndef BEBONE_TYPES_RAND
    #define BEBONE_TYPES_RAND rand()
#endif

#include "color_format.h"

#include <glad/glad.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace bebone::core {
    template<ColorFormat Format>
    struct Color {

    };
}

#endif
