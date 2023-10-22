#ifndef _SHADER_VERTEX_H_
#define _SHADER_VERTEX_H_

#include "bebone/bebone.h"

namespace game::core {
    using namespace bebone::core;

    struct ShaderVertex {
        Vec2f position;
        Vec2f textureCoordinates;
    };
}

#endif
