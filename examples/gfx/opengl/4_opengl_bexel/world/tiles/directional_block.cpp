#include "directional_block.h"

#include "../chunk.h"
#include "../world.h"

namespace bexel {
    DirectionalBlock::DirectionalBlock(const Vec3f& chunk_position) : Block(chunk_position) {

    }

    void DirectionalBlock::append_mesh(MeshBuilder& mesh_builder, World& world, Chunk& chunk) {
        const auto chunk_pos = chunk.get_pos();

        const auto& x = chunk_position.x + chunk_pos.x;
        const auto& y = chunk_position.y + chunk_pos.y;
        const auto& z = chunk_position.z + chunk_pos.z;

        auto up_block =      world.get_voxel_at(Vec3f(x, y + 1.0f, z));
        auto down_block =    world.get_voxel_at(Vec3f(x, y - 1.0f, z));
        auto left_block =    world.get_voxel_at(Vec3f(x + 1.0f, y, z));
        auto right_block =   world.get_voxel_at(Vec3f(x - 1.0f, y, z));
        auto forward_block = world.get_voxel_at(Vec3f(x, y, z + 1.0f));
        auto back_block =    world.get_voxel_at(Vec3f(x, y, z - 1.0f));

        if(up_block != Solid) {
            mesh_builder.append(
            WallMesh<Up>{},
            get_up_tex_coords(),
            Transform{chunk_position, Mat4f::identity(), Vec3f::one
            });
        }

        if(down_block != Solid) {
            mesh_builder.append(
            WallMesh<Down>{},
            get_down_tex_coords(),
            Transform{chunk_position, Mat4f::identity(), Vec3f::one
            });
        }

        if(left_block != Solid) {
            mesh_builder.append(
            WallMesh<Left>{},
            get_left_tex_coords(),
            Transform{chunk_position, Mat4f::identity(), Vec3f::one
            });
        }

        if(right_block != Solid) {
            mesh_builder.append(
            WallMesh<Right>{},
            get_right_tex_coords(),
            Transform{chunk_position, Mat4f::identity(), Vec3f::one
            });
        }

        if(forward_block != Solid) {
            mesh_builder.append(
            WallMesh<Forward>{},
            get_forward_tex_coords(),
            Transform{chunk_position, Mat4f::identity(), Vec3f::one
            });
        }

        if(back_block != Solid) {
            mesh_builder.append(
            WallMesh<Back>{},
            get_back_tex_coords(),
            Transform{chunk_position, Mat4f::identity(), Vec3f::one
            });
        }
    }
}
