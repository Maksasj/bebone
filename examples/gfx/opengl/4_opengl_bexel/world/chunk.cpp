#include "chunk.h"
#include "world.h"

namespace bexel {
    Chunk::Chunk(const Vec3f& pos) : m_mesh(nullptr) {
        m_transform.translation = pos;
        m_transform.rotation = Mat4f::identity();
        m_transform.scale = Vec3f::one;
    }

    Chunk::~Chunk() {
        for(i32 x = 0; x < CHUNK_SIZE_X; ++x) {
            for(i32 z = 0; z < CHUNK_SIZE_Z; ++z) {
                for(i32 y = 0; y < CHUNK_SIZE_Y; ++y) {
                    delete m_voxels[x][y][z];
                }
            }
        }
    }

    void Chunk::generate_chunk(unique_ptr<WorldGenerator>& worldGenerator) {
        for(i32 x = 0; x < CHUNK_SIZE_X; ++x) {
            for(i32 z = 0; z < CHUNK_SIZE_Z; ++z) {
                for(i32 y = 0; y < CHUNK_SIZE_Y; ++y) {
                    m_voxels[x][y][z] = worldGenerator->create_voxel_at(*this, Vec3i(x, y, z));
                }
            }
        }
    }

    TileBlock* Chunk::get_voxel(const i32& x, const i32& y, const i32& z) {
        if(x < 0 || x >= CHUNK_SIZE_X) return nullptr;
        if(y < 0 || y >= CHUNK_SIZE_Y) return nullptr;
        if(z < 0 || z >= CHUNK_SIZE_Z) return nullptr;

        return m_voxels[x][y][z];
    }

    const Vec3f& Chunk::get_pos() const {
        return m_transform.translation;
    }

    void Chunk::generate_mesh(World& world) {
        MeshBuilder meshBuilder;

        for(i32 x = 0; x < CHUNK_SIZE_X; ++x) {
            for(i32 z = 0; z < CHUNK_SIZE_Z; ++z) {
                for(i32 y = 0; y < CHUNK_SIZE_Y; ++y) {
                    auto voxel = get_voxel(x, y, z);

                    if(voxel != nullptr)
                        voxel->append_mesh(meshBuilder, world, *this);
                }
            }
        }

        m_mesh = meshBuilder.build();
    }

    const Transform& Chunk::get_transform() const {
        return m_transform;
    }

    void Chunk::render(unique_ptr<GLShaderProgram>& shader) {
        shader->set_uniform("transform", m_transform.calc_matrix());

        if(m_mesh != nullptr)
            m_mesh->render();
    }
}
