#include "chunk.h"
#include "world.h"

namespace bexel {
    Chunk::Chunk(const Vec3f& pos) : m_mesh(nullptr) {
        m_ubo = make_unique<GLUniformBufferObject>(sizeof(Mat4f));

        m_transform.translation = pos;
        m_transform.rotation = Mat4f::identity();
        m_transform.scale = Vec3f::splat(1.0f);
    }

    Chunk::~Chunk() {
        for(i32 x = 0; x < 16; ++x) {
            for(i32 z = 0; z < 16; ++z) {
                for(i32 y = 0; y < 16; ++y) {
                    delete m_voxels[x][y][z];
                }
            }
        }
    }

    void Chunk::generate_chunk(unique_ptr<WorldGenerator>& worldGenerator) {
        for(i32 x = 0; x < 16; ++x) {
            for(i32 z = 0; z < 16; ++z) {
                for(i32 y = 0; y < 16; ++y) {
                    m_voxels[x][y][z] = worldGenerator->create_voxel_at(*this, Vec3i(x, y, z));
                }
            }
        }
    }

    TileBlock* Chunk::get_voxel(const i32& x, const i32& y, const i32& z) {
        if(x < 0 || x >= 16) return nullptr;
        if(y < 0 || y >= 16) return nullptr;
        if(z < 0 || z >= 16) return nullptr;

        return m_voxels[x][y][z];
    }

    const Vec3f& Chunk::get_pos() const {
        return m_transform.translation;
    }

    void Chunk::generate_mesh(World& world) {
        MeshBuilder meshBuilder;

        for(i32 x = 0; x < 16; ++x) {
            for(i32 z = 0; z < 16; ++z) {
                for(i32 y = 0; y < 16; ++y) {
                    auto voxel = get_voxel(x, y, z);

                    if(voxel != nullptr)
                        voxel->append_mesh(meshBuilder, world, *this);
                }
            }
        }

        m_mesh = meshBuilder.build();
    }

    void Chunk::render(unique_ptr<GLShaderProgram>& shader) {
        m_ubo->bind();
            shader->bind_buffer("Transform", 0, *m_ubo);
            auto transform = static_cast<Mat4f*>(m_ubo->map());
            *transform = m_transform.calc_matrix();
            m_ubo->unmap();
        m_ubo->unbind();

        if(m_mesh != nullptr)
            m_mesh->render();
    }
}
