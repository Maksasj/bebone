#ifndef BEXEL_GRASS_BLOCK_H
#define BEXEL_GRASS_BLOCK_H

#include "side_directional_block.h"

namespace bexel {
    class GrassBlock : public SideDirectionalBlock {
        private:

        public:
            GrassBlock(const Vec3f &chunkPosition);

            const vector<Vec2f>& get_up_tex_coords() override {
                static const vector<Vec2f> coordinates = {
                    {0.03125f, 1.0f - 0.03125f},
                    {0.03125f, 1.0f - 0.0f},
                    {0.0f, 1.0f - 0.0f},
                    {0.0f, 1.0f - 0.03125f}
                };

                return coordinates;
            }

            const vector<Vec2f>& get_down_tex_coords() override {
                static const vector<Vec2f> coordinates = {
                    {0.03125f, 1.0f - 0.03125f},
                    {0.03125f, 0.0f},
                    {0.0f, 0.0f},
                    {0.0f, 1.0f - 0.03125f}
                };

                return coordinates;
            }

            const vector<Vec2f>& get_forward_tex_coords() override {
                static const vector<Vec2f> coordinates = {
                    {0.03125f * 2, 1.0f - 0.03125f},
                    {0.03125f * 2, 1.0f - 0.0f},
                    {0.03125f, 1.0f - 0.0f},
                    {0.03125f, 1.0f - 0.03125f}
                };

                return coordinates;
            }
    };
}

#endif
