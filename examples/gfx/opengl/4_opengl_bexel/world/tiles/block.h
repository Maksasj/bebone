#ifndef BEXEL_BLOCK_H
#define BEXEL_BLOCK_H

#include "tile_block.h"

namespace bexel {
    class Block : public TileBlock {
        private:

        protected:
            Vec3f m_chunkPosition;

        public:
            Block(const Vec3f& chunkPosition);

            void append_mesh(MeshBuilder& meshBuilder, World& world, Chunk& chunk) override;
    };
}

#endif
