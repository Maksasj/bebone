#ifndef CHUNK_H
#define CHUNK_H

#include "mesh.h"
#include "renderable.h"

namespace bexel {
    class Chunk : public Renderable {
        private:

        public:
            void render(unique_ptr<GLShaderProgram>& shader) override {

            }
    };
}

#endif
