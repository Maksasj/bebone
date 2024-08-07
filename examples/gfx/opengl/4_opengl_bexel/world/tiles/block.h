#ifndef BEXEL_BLOCK_H
#define BEXEL_BLOCK_H

#include "tile_block.h"

namespace bexel {
    class Block : public TileBlock {
        private:

        protected:
            Vec3f chunk_position;

        public:
            Block(const Vec3f& chunk_position);

            void append_mesh(MeshBuilder& mesh_builder, World& world, Chunk& chunk) override;
    };
}

#endif
