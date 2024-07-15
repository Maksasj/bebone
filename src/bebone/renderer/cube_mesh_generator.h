#ifndef _BEBONE_RENDERER_CUBE_MESH_GENERATOR_H_
#define _BEBONE_RENDERER_CUBE_MESH_GENERATOR_H_

#include "renderer_backend.h"
#include "imesh_generator.h"

namespace bebone::renderer {
    class CubeMeshGenerator : public IMeshGenerator<Vertex> {
        public:
            CubeMeshGenerator(const std::shared_ptr<IMeshBuilder<Vertex>>& builder);

            void reset() override;
            std::shared_ptr<IMesh> generate() override;
    };
}

#endif
