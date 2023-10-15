#ifndef BEXEL_CHUNK_H
#define BEXEL_CHUNK_H

#include "../mesh/mesh.h"
#include "../mesh/mesh_builder.h"
#include "../mesh/wall_mesh.h"

#include "../renderable.h"
#include "../transform.h"

#include "world_generator.h"
#include "tile_block.h"

namespace bexel {
    class World;

    class Chunk final : public Renderable, private core::NonCopyable {
        private:
            array<array<array<TileBlock*, 16>, 16>, 16> m_voxels;
            Transform m_transform;

            unique_ptr<Mesh> m_mesh;
            unique_ptr<GLUniformBufferObject> m_ubo;

        public:
            Chunk(const Vec3f& pos);
            ~Chunk();

            void generate_chunk(unique_ptr<WorldGenerator>& worldGenerator);
            void generate_mesh(World& world);

            TileBlock* get_voxel(const i32& x, const i32& y, const i32& z);
            const Vec3f& get_pos() const;

            void render(unique_ptr<GLShaderProgram>& shader) override;
    };
}

#endif
