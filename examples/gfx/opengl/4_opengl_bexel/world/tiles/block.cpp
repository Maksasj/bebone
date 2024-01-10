#include "block.h"

#include "gfx/opengl/4_opengl_bexel/world/chunk.h"
#include "gfx/opengl/4_opengl_bexel/world/world.h"

namespace bexel {
    Block::Block(const Vec3f& chunkPosition) : TileBlock(false), m_chunkPosition(chunkPosition) {

    }

    void Block::append_mesh(MeshBuilder& meshBuilder, World& world, Chunk& chunk) {
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

        if(upBlock != SOLID)
            meshBuilder.append(
            WallMesh<UP>{},
            Transform{m_chunkPosition,Mat4f::identity(),Vec3f::one}
        );

        if(downBlock != SOLID)
            meshBuilder.append(
            WallMesh<DOWN>{},
            Transform{m_chunkPosition,Mat4f::identity(),Vec3f::one}
        );

        if(leftBlock != SOLID)
            meshBuilder.append(
            WallMesh<LEFT>{},
            Transform{m_chunkPosition,Mat4f::identity(),Vec3f::one}
        );

        if(rightBlock != SOLID)
            meshBuilder.append(
            WallMesh<RIGHT>{},
            Transform{m_chunkPosition,Mat4f::identity(),Vec3f::one}
        );

        if(forwardBlock != SOLID)
            meshBuilder.append(
            WallMesh<FORWARD>{},
            Transform{m_chunkPosition,Mat4f::identity(),Vec3f::one}
        );

        if(backBlock != SOLID)
            meshBuilder.append(
            WallMesh<BACK>{},
            Transform{m_chunkPosition,Mat4f::identity(),Vec3f::one}
        );
    }
}
