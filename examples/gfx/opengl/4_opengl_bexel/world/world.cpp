#include "world.h"

namespace bexel {
    World::World() : m_worldGenerator(nullptr), m_chunkUbo(nullptr) {
        m_worldGenerator = make_unique<WorldGenerator>(123);

        m_chunkUbo = make_unique<GLUniformBufferObject>(sizeof(Mat4f));
    }

    BlockID World::get_voxel_at(const Vec3f& voxelPos) const {
        return m_worldGenerator->get_voxel_at(voxelPos);
    }

    bool World::chunk_exist(const Vec2i& pos) const {
        return m_chunks.find(pos) != m_chunks.end();
    }

    void World::update(unique_ptr<Camera>& camera) {
        const auto pos = camera->get_position();
        const auto camChunkPos = Vec2i(
            static_cast<i32>(pos.x) / CHUNK_SIZE_X,
            static_cast<i32>(pos.z) / CHUNK_SIZE_Z
        );

        static auto prevChunkPos = Vec2i(camChunkPos.x + 1, camChunkPos.x);

        if(prevChunkPos == camChunkPos)
            return;

        const auto renderDistance = camera->get_render_distance();

        for(auto x = -renderDistance; x < renderDistance; ++x) {
            for(auto z = -renderDistance; z < renderDistance; ++z) {
                const auto toCheck = camChunkPos + Vec2i(x, z);

                if(chunk_exist(toCheck))
                    continue;

                const auto createChunkPos = Vec3f(
                    static_cast<f32>(toCheck.x) * CHUNK_SIZE_X,
                    0.0f,
                    static_cast<f32>(toCheck.y) * CHUNK_SIZE_Z
                );

                m_chunks[toCheck] = make_unique<Chunk>(createChunkPos);
                m_chunks[toCheck]->generate_chunk(m_worldGenerator);
                m_chunks[toCheck]->generate_mesh(*this);
            }
        }
    }

    void World::render(unique_ptr<GLShaderProgram>& shader) {
        for_each(m_chunks.begin(), m_chunks.end(), [&](auto& tuple) {
            unique_ptr<Chunk>& chunk = tuple.second;

            // Need to check if we really need to have this there
            m_chunkUbo->bind();
            shader->bind_buffer("Transform", 0, *m_chunkUbo);
            auto transform = static_cast<Mat4f*>(m_chunkUbo->map());
            *transform = chunk->get_transform().calc_matrix();
            m_chunkUbo->unmap();
            m_chunkUbo->unbind();

            chunk->render(shader);
        });
    };
}
