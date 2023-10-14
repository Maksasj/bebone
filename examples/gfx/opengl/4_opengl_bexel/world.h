#ifndef WORLD_H
#define WORLD_H

#include "chunk.h"
#include "renderable.h"

namespace bexel {
    class World : public Renderable {
        private:
            unique_ptr<WorldGenerator> m_worldGenerator;

        public:
            World();

            void update();
            void render(unique_ptr<GLShaderProgram>& shader) override;
    };
}

#endif
