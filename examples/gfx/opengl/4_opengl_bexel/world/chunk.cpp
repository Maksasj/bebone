#include "chunk.h"
#include "world.h"

namespace bexel {
    Chunk::Chunk(const Vec3f& pos) : mesh(nullptr) {
        transform.translation = pos;
        transform.rotation = Mat4f::identity();
        transform.scale = Vec3f::one;
    }

    Chunk::~Chunk() {
        for(i32 x = 0; x < CHUNK_SIZE_X; ++x) {
            for(i32 z = 0; z < CHUNK_SIZE_Z; ++z) {
                for(i32 y = 0; y < CHUNK_SIZE_Y; ++y) {
                    delete voxels[x][y][z];
                }
            }
        }
    }

    void Chunk::generate_chunk(unique_ptr<WorldGenerator>& world_generator) {
        for(i32 x = 0; x < CHUNK_SIZE_X; ++x) {
            for(i32 z = 0; z < CHUNK_SIZE_Z; ++z) {
                for(i32 y = 0; y < CHUNK_SIZE_Y; ++y) {
                    voxels[x][y][z] = world_generator->create_voxel_at(*this, Vec3i(x, y, z));
                }
            }
        }
    }

    TileBlock* Chunk::get_voxel(const i32& x, const i32& y, const i32& z) {
        if(x < 0 || x >= CHUNK_SIZE_X) return nullptr;
        if(y < 0 || y >= CHUNK_SIZE_Y) return nullptr;
        if(z < 0 || z >= CHUNK_SIZE_Z) return nullptr;

        return voxels[x][y][z];
    }

    const Vec3f& Chunk::get_pos() const {
        return transform.translation;
    }

    void Chunk::generate_mesh(World& world) {
        MeshBuilder mesh_builder;

        for(i32 x = 0; x < CHUNK_SIZE_X; ++x) {
            for(i32 z = 0; z < CHUNK_SIZE_Z; ++z) {
                for(i32 y = 0; y < CHUNK_SIZE_Y; ++y) {
                    auto voxel = get_voxel(x, y, z);

                    if(voxel != nullptr)
                        voxel->append_mesh(mesh_builder, world, *this);
                }
            }
        }

        mesh = mesh_builder.build();
    }

    const Transform& Chunk::get_transform() const {
        return transform;
    }

    void Chunk::render(unique_ptr<GLShaderProgram>& shader) {
        shader->set_uniform("transform", transform.calc_matrix());

        if(mesh != nullptr)
            mesh->render();
    }
}
