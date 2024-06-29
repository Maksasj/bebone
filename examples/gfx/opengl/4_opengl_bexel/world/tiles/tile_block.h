#ifndef BEXEL_TILE_BLOCK_H
#define BEXEL_TILE_BLOCK_H

#include "mesh/vertex.h"
#include "mesh/mesh_builder.h"

namespace bexel {
    class Chunk;
    class World;

    class TileBlock {
        private:
            bool opaque;

        public:
            TileBlock(const bool& opaque) : opaque(opaque) {

            }

            virtual ~TileBlock() = default;

            const bool& is_opaque() const {
                return opaque;
            }

            virtual void append_mesh(MeshBuilder& mesh_builder, World& world, Chunk& chunk) = 0;
    };
}

#endif
