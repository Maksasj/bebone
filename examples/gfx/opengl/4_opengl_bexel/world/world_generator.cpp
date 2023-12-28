#include "world_generator.h"
#include "chunk.h"

namespace bexel {
    WorldGenerator::WorldGenerator(const i32& seed) : m_seed(seed) {

    }

    BlockID WorldGenerator::get_voxel_at(const Vec3f& voxelPosF) const {
        const auto& x = voxelPosF.x;
        const auto& y = voxelPosF.y;
        const auto& z = voxelPosF.z;

        auto v0 = stb_perlin_noise3_seed(x * 0.05f, 0, z * 0.05f,0, 0, 0, m_seed) * 0.5f + 0.5f;
        auto v1 = stb_perlin_noise3_seed(x * 0.01f, 0, z * 0.01f,0, 0, 0, m_seed) * 0.5f + 0.5f;

        const auto v = v0 * 8.0f + v1 * 24.0f;

        if(y > v)
            return AIR;

        return SOLID;
    }

    TileBlock* WorldGenerator::create_voxel_at(const Chunk& chunk, const Vec3i& voxelPosI) const {
        const auto voxelPosF = Vec3f(
            static_cast<f32>(voxelPosI.x),
            static_cast<f32>(voxelPosI.y),
            static_cast<f32>(voxelPosI.z)
        );

        const auto& chunkPos = chunk.get_pos();
        const auto globalPos = chunkPos + voxelPosF;

        const auto blockID = get_voxel_at(globalPos);

        switch (blockID) {
            case SOLID: return new GrassBlock(voxelPosF);
            default: return nullptr;
        }
    }
}
