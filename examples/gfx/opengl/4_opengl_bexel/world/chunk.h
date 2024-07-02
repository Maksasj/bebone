#ifndef BEXEL_CHUNK_H
#define BEXEL_CHUNK_H

#include "../mesh/mesh.h"
#include "../mesh/mesh_builder.h"
#include "../mesh/wall_mesh.h"

#include "../renderable.h"
#include "../transform.h"

#include "world_generator.h"
#include "world/tiles/tile_block.h"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 32
#define CHUNK_SIZE_Z 16

namespace bexel {
    class World;

    class Chunk final : public Renderable, private core::NonCopyable {
        private:
            array<array<array<TileBlock*, CHUNK_SIZE_Z>, CHUNK_SIZE_Y>, CHUNK_SIZE_X> voxels;
            Transform transform;

            unique_ptr<Mesh> mesh;

        public:
            Chunk(const Vec3f& pos);
            ~Chunk();

            void generate_chunk(unique_ptr<WorldGenerator>& world_generator);
            void generate_mesh(World& world);

            TileBlock* get_voxel(const i32& x, const i32& y, const i32& z);
            const Vec3f& get_pos() const;

            const Transform& get_transform() const;
            void render(unique_ptr<GLShaderProgram>& shader) override;
    };
}

#endif
