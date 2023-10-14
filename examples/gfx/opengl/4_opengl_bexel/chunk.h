#ifndef BEXEL_CHUNK_H
#define BEXEL_CHUNK_H

#include "mesh.h"
#include "renderable.h"
#include "voxel.h"
#include "transform.h"

#define BEXEL_CHUNK_WIDTH 16
#define BEXEL_CHUNK_LENGTH 16
#define BEXEL_CHUNK_HEIGHT 16

namespace bexel {
    class Chunk : public Renderable {
        private:
            Voxel m_voxels[BEXEL_CHUNK_WIDTH][BEXEL_CHUNK_LENGTH][BEXEL_CHUNK_HEIGHT];
            Transform m_transform;

            unique_ptr<Mesh> m_mesh;
            unique_ptr<GLUniformBufferObject> m_ubo;

        public:
            Chunk(const Vec3f& pos);

            void generate_mesh();

            void render(unique_ptr<GLShaderProgram>& shader) override;
    };
}

#endif
