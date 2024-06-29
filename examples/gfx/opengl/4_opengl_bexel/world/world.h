#ifndef WORLD_H
#define WORLD_H

#include <thread>
#include <execution>
#include <ranges>

#include "chunk.h"
#include "renderable.h"
#include "camera.h"

namespace bexel {
    class World final : public Renderable, private core::NonCopyable {
        private:
            unique_ptr<WorldGenerator> world_generator;
            unordered_map<Vec2i, unique_ptr<Chunk>> chunks;

            bool chunk_exist(const Vec2i& pos) const;

        public:
            World();

            BlockID get_voxel_at(const Vec3f& voxel_pos) const;

            void update(unique_ptr<Camera>& camera);
            void render(unique_ptr<GLShaderProgram>& shader) override;
    };
}

#endif
