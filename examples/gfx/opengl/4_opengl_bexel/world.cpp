#include "world.h"

namespace bexel {
    World::World() : m_worldGenerator(nullptr) {
        m_worldGenerator = make_unique<WorldGenerator>(123);
    }

    bool World::chunk_exist(const Vec2i& pos) const {
        return m_chunks.find(pos) != m_chunks.end();
    }

    void World::update(unique_ptr<Camera>& camera) {
        const auto pos = camera->get_position();
        const auto camChunkPos = Vec2i(
            static_cast<i32>(pos.x) / 16,
            static_cast<i32>(pos.z) / 16
        );

        const auto renderDistance = camera->get_render_distance();

        for(auto x = -+renderDistance; x < renderDistance; ++x) {
            for(auto z = -renderDistance; z < renderDistance; ++z) {
                const auto toCheck = camChunkPos + Vec2i(x, z);

                if(chunk_exist(toCheck)) {
                    continue;
                }

                const auto createChunkPos = Vec3f(
                    static_cast<f32>(toCheck.x) * 16.0f,
                    0.0f,
                    static_cast<f32>(toCheck.y) * 16.0f
                );

                m_chunks[toCheck] = make_unique<Chunk>(createChunkPos);
                m_chunks[toCheck]->generate_chunk(m_worldGenerator);
                m_chunks[toCheck]->generate_mesh();
            }
        }
    }

    void World::render(unique_ptr<GLShaderProgram>& shader) {
        for_each(m_chunks.begin(), m_chunks.end(), [&](auto& tuple) {
            auto& chunk = tuple.second;
            chunk->render(shader);
        });
    };
}
