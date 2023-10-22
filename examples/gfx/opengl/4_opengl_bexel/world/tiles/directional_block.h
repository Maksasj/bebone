#ifndef BEXEL_DIRECTIONAL_BLOCK_H
#define BEXEL_DIRECTIONAL_BLOCK_H

#include "block.h"

namespace bexel {
    class DirectionalBlock : public Block {
        private:

        public:
            DirectionalBlock(const Vec3f& chunkPosition);

            virtual const vector<Vec2f>& get_up_tex_coords() = 0;
            virtual const vector<Vec2f>& get_down_tex_coords() = 0;
            virtual const vector<Vec2f>& get_left_tex_coords() = 0;
            virtual const vector<Vec2f>& get_right_tex_coords() = 0;
            virtual const vector<Vec2f>& get_forward_tex_coords() = 0;
            virtual const vector<Vec2f>& get_back_tex_coords() = 0;

            void append_mesh(MeshBuilder& meshBuilder, World& world, Chunk& chunk) override;
    };
}

#endif
