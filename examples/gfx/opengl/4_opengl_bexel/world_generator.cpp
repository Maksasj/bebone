#include "world_generator.h"

namespace bexel {
    WorldGenerator::WorldGenerator(const i32& seed) : m_seed(seed) {

    }

    Voxel WorldGenerator::get_voxel_at(const Vec3f& pos) const {
        const auto value = stb_perlin_noise3_seed(pos.x, pos.y, pos.z, 0, 0, 0, m_seed);

        if(value < 0.5)
            return Voxel{false};

        return Voxel{true};
    }
}
