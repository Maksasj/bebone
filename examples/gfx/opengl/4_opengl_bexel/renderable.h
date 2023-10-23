#ifndef BEXEL_RENDERABLE_H
#define BEXEL_RENDERABLE_H

#include "gfx/opengl/4_opengl_bexel/mesh/vertex.h"

namespace bexel {
    class Renderable {
        public:
            virtual void render(unique_ptr<GLShaderProgram>& shader) = 0;
    };
}

#endif
