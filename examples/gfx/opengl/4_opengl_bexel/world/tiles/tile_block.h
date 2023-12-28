#ifndef BEXEL_TILE_BLOCK_H
#define BEXEL_TILE_BLOCK_H

#include "gfx/opengl/4_opengl_bexel/mesh/vertex.h"
#include "gfx/opengl/4_opengl_bexel/mesh/mesh_builder.h"

namespace bexel {
    class Chunk;
    class World;

    class TileBlock {
        private:
            bool m_opaque;

        public:
            TileBlock(const bool& opaque) : m_opaque(opaque) {

            }

            virtual ~TileBlock() = default;

            const bool& is_opaque() const {
                return m_opaque;
            }

            virtual void append_mesh(MeshBuilder& meshBuilder, World& world, Chunk& chunk) = 0;
    };
}

#endif
