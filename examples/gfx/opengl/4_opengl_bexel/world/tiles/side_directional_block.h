#ifndef BEXEL_SIDE_DIRECTIONAL_BLOCK
#define BEXEL_SIDE_DIRECTIONAL_BLOCK

#include "directional_block.h"

namespace bexel {
    class SideDirectionalBlock : public DirectionalBlock {
        private:

        public:
            SideDirectionalBlock(const Vec3f& chunkPosition);

            const vector<Vec2f>& get_left_tex_coords() override {
                return get_forward_tex_coords();
            }

            const vector<Vec2f>& get_right_tex_coords() override {
                return get_forward_tex_coords();
            }

            const vector<Vec2f>& get_back_tex_coords() override {
                return get_forward_tex_coords();
            }
    };
}

#endif
