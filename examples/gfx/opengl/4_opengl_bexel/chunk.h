#ifndef BEXEL_CHUNK_H
#define BEXEL_CHUNK_H

#include "mesh.h"
#include "renderable.h"
#include "voxel.h"
#include "transform.h"
#include "world_generator.h"

namespace bexel {
    class Chunk : public Renderable {
        private:
            array<array<array<Voxel, 16>, 16>, 16> m_voxels;
            Transform m_transform;

            unique_ptr<Mesh> m_mesh;
            unique_ptr<GLUniformBufferObject> m_ubo;

        public:
            Chunk(const Vec3f& pos);

            void generate_chunk(unique_ptr<WorldGenerator>& worldGenerator);

            void generate_mesh();

            void render(unique_ptr<GLShaderProgram>& shader) override;
    };
}

#endif
