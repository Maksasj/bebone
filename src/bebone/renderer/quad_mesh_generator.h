#ifndef _BEBONE_RENDERER_QUAD_MESH_GENERATOR_H_
#define _BEBONE_RENDERER_QUAD_MESH_GENERATOR_H_

#include "renderer_backend.h"
#include "mesh/imesh_generator.h"

namespace bebone::renderer {
    class QuadMeshGenerator : public IMeshGenerator<Vertex> {
        public:
            QuadMeshGenerator(const std::shared_ptr<IMeshBuilder<Vertex>>& builder);

            void reset() override;
            std::shared_ptr<IMesh> generate() override;
    };

}

#endif
