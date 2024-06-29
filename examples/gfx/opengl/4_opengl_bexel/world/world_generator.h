#ifndef BEXEL_WORLD_GENERATOR_H
#define BEXEL_WORLD_GENERATOR_H

#include <stb_perlin.h>

#include "block_id.h"
#include "tiles/blocks.h"

namespace bexel {
    class Chunk;

    class WorldGenerator {
        private:
            const i32 seed;

        public:
            WorldGenerator(const i32& seed);

            BlockID get_voxel_at(const Vec3f& voxel_pos_f) const;
            TileBlock* create_voxel_at(const Chunk& chunk, const Vec3i& voxel_pos_i) const;
    };
}

#endif
