#include "world_generator.h"
#include "chunk.h"

namespace bexel {
    WorldGenerator::WorldGenerator(const i32& seed) : seed(seed) {

    }

    BlockID WorldGenerator::get_voxel_at(const Vec3f& voxel_pos_f) const {
        const auto& x = voxel_pos_f.x;
        const auto& y = voxel_pos_f.y;
        const auto& z = voxel_pos_f.z;

        auto v0 = stb_perlin_noise3_seed(x * 0.05f, 0, z * 0.05f,0, 0, 0, seed) * 0.5f + 0.5f;
        auto v1 = stb_perlin_noise3_seed(x * 0.01f, 0, z * 0.01f,0, 0, 0, seed) * 0.5f + 0.5f;

        const auto v = v0 * 8.0f + v1 * 24.0f;

        if(y > v)
            return Air;

        return Solid;
    }

    TileBlock* WorldGenerator::create_voxel_at(const Chunk& chunk, const Vec3i& voxel_pos_i) const {
        const auto voxel_pos_f = Vec3f(
            static_cast<f32>(voxel_pos_i.x),
            static_cast<f32>(voxel_pos_i.y),
            static_cast<f32>(voxel_pos_i.z)
        );

        const auto& chunk_pos = chunk.get_pos();
        const auto global_pos = chunk_pos + voxel_pos_f;

        const auto block_id = get_voxel_at(global_pos);

        switch (block_id) {
            case Solid: return new GrassBlock(voxel_pos_f);
            default: return nullptr;
        }
    }
}
