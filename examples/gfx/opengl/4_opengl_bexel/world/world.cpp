#include "world.h"

namespace bexel {
    World::World() : world_generator(nullptr) {
        world_generator = make_unique<WorldGenerator>(123);
    }

    BlockID World::get_voxel_at(const Vec3f& voxel_pos) const {
        return world_generator->get_voxel_at(voxel_pos);
    }

    bool World::chunk_exist(const Vec2i& pos) const {
        return chunks.find(pos) != chunks.end();
    }

    void World::update(unique_ptr<Camera>& camera) {
        const auto pos = camera->get_position();
        const auto cam_chunk_pos = Vec2i(
            static_cast<i32>(pos.x) / CHUNK_SIZE_X,
            static_cast<i32>(pos.z) / CHUNK_SIZE_Z
        );

        static auto prev_chunk_pos = Vec2i(cam_chunk_pos.x + 1, cam_chunk_pos.x);

        if(prev_chunk_pos == cam_chunk_pos)
            return;

        const auto render_distance = camera->get_render_distance();

        for(auto x = -render_distance; x < render_distance; ++x) {
            for(auto z = -render_distance; z < render_distance; ++z) {
                const auto to_check = cam_chunk_pos + Vec2i(x, z);

                if(chunk_exist(to_check))
                    continue;

                const auto create_chunk_pos = Vec3f(
                    static_cast<f32>(to_check.x) * CHUNK_SIZE_X,
                    0.0f,
                    static_cast<f32>(to_check.y) * CHUNK_SIZE_Z
                );

                chunks[to_check] = make_unique<Chunk>(create_chunk_pos);
                chunks[to_check]->generate_chunk(world_generator);
                chunks[to_check]->generate_mesh(*this);
            }
        }
    }

    void World::render(unique_ptr<GLShaderProgram>& shader) {
        for_each(chunks.begin(), chunks.end(), [&](const auto& tuple) {
            const auto& chunk = tuple.second;
            chunk->render(shader);
        });
    };
}
