#ifndef BEXEL_RENDERABLE_H
#define BEXEL_RENDERABLE_H

#include "vertex.h"

namespace bexel {
    class Renderable {
        public:
            virtual void render(unique_ptr<GLShaderProgram>& shader) = 0;
    };
}

#endif
