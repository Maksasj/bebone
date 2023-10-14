#ifndef BEXEL_WORLD_GENERATOR_H
#define BEXEL_WORLD_GENERATOR_H

#include "stb_perlin.h"

#include "voxel.h"

namespace bexel {
    class WorldGenerator {
        private:
            const i32 m_seed;

        public:
            WorldGenerator(const i32& seed);

            Voxel get_voxel_at(const Vec3f& pos) const;
    };
}

#endif
