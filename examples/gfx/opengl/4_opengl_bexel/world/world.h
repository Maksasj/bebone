#ifndef WORLD_H
#define WORLD_H

#include <thread>
#include <execution>
#include <ranges>

#include "chunk.h"
#include "renderable.h"
#include "camera.h"

namespace std {
    template <>
    struct hash<omni::types::Vec2i> {
        size_t operator()(const omni::types::Vec2i& key) const {
            return std::hash<int>()(key.x) ^ std::hash<int>()(key.y);
        }
    };
}

namespace bexel {
    class World final : public Renderable, private core::NonCopyable {
        private:
            unique_ptr<WorldGenerator> m_worldGenerator;
            unordered_map<Vec2i, unique_ptr<Chunk>> m_chunks;

            unique_ptr<GLUniformBufferObject> m_chunkUbo;

            bool chunk_exist(const Vec2i& pos) const;

        public:
            World();

            BlockID get_voxel_at(const Vec3f& voxelPos) const;

            void update(unique_ptr<Camera>& camera);
            void render(unique_ptr<GLShaderProgram>& shader) override;
    };
}

#endif
