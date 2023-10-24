#include "directional_block.h"

#include "../chunk.h"
#include "../world.h"

namespace bexel {
    DirectionalBlock::DirectionalBlock(const Vec3f& chunkPosition) : Block(chunkPosition) {

    }

    void DirectionalBlock::append_mesh(MeshBuilder& meshBuilder, World& world, Chunk& chunk) {
        const auto chunkPos = chunk.get_pos();

        const auto& x = m_chunkPosition.x + chunkPos.x;
        const auto& y = m_chunkPosition.y + chunkPos.y;
        const auto& z = m_chunkPosition.z + chunkPos.z;

        auto upBlock =      world.get_voxel_at(Vec3f(x, y + 1.0f, z));
        auto downBlock =    world.get_voxel_at(Vec3f(x, y - 1.0f, z));
        auto leftBlock =    world.get_voxel_at(Vec3f(x + 1.0f, y, z));
        auto rightBlock =   world.get_voxel_at(Vec3f(x - 1.0f, y, z));
        auto forwardBlock = world.get_voxel_at(Vec3f(x, y, z + 1.0f));
        auto backBlock =    world.get_voxel_at(Vec3f(x, y, z - 1.0f));

        if(upBlock != SOLID) {
            meshBuilder.append(
            WallMesh<UP>{},
            get_up_tex_coords(),
            Transform{m_chunkPosition,Mat4f::identity(),Vec3f::splat(1.0f)
            });
        }

        if(downBlock != SOLID) {
            meshBuilder.append(
            WallMesh<DOWN>{},
            get_down_tex_coords(),
            Transform{m_chunkPosition,Mat4f::identity(),Vec3f::splat(1.0f)
            });
        }

        if(leftBlock != SOLID) {
            meshBuilder.append(
            WallMesh<LEFT>{},
            get_left_tex_coords(),
            Transform{m_chunkPosition,Mat4f::identity(),Vec3f::splat(1.0f)
            });
        }

        if(rightBlock != SOLID) {
            meshBuilder.append(
            WallMesh<RIGHT>{},
            get_right_tex_coords(),
            Transform{m_chunkPosition,Mat4f::identity(),Vec3f::splat(1.0f)
            });
        }

        if(forwardBlock != SOLID) {
            meshBuilder.append(
            WallMesh<FORWARD>{},
            get_forward_tex_coords(),
            Transform{m_chunkPosition,Mat4f::identity(),Vec3f::splat(1.0f)
            });
        }

        if(backBlock != SOLID) {
            meshBuilder.append(
            WallMesh<BACK>{},
            get_back_tex_coords(),
            Transform{m_chunkPosition,Mat4f::identity(),Vec3f::splat(1.0f)
            });
        }
    }
}
