#include "chunk.h"

namespace bexel {
    Chunk::Chunk(const Vec3f& pos) : m_mesh(nullptr) {
        m_ubo = make_unique<GLUniformBufferObject>(sizeof(Transform));

        m_transform.translation = Mat4f::translation(pos);

        generate_mesh();
    }

    void Chunk::generate_mesh() {
        vector<Vertex> vertices = {
            // positions          // colors
            {{-0.5, -0.5,  0.5},    {1.0f, 1.0f, 1.0f}},
            {{0.5, -0.5,  0.5},     {1.0f, 1.0f, 0.0f}},
            {{0.5,  0.5,  0.5},     {1.0f, 0.0f, 1.0f}},
            {{-0.5,  0.5,  0.5},    {1.0f, 0.0f, 0.0f}},
            {{-0.5, -0.5, -0.5},    {0.0f, 1.0f, 1.0f}},
            {{0.5, -0.5, -0.5},     {0.0f, 1.0f, 0.0f}},
            {{0.5,  0.5, -0.5},     {0.0f, 0.0f, 1.0f}},
            {{-0.5,  0.5, -0.5},    {0.0f, 0.0f, 0.0f}}
        };

        vector<u32> indices = {
            0, 1, 2, 2, 3, 0,
            1, 5, 6, 6, 2, 1,
            7, 6, 5, 5, 4, 7,
            4, 0, 3, 3, 7, 4,
            4, 5, 1, 1, 0, 4,
            3, 2, 6, 6, 7, 3
        };

        m_mesh = make_unique<Mesh>(vertices, indices);
    }

    void Chunk::render(unique_ptr<GLShaderProgram>& shader) {
        m_ubo->bind();
        shader->bind_buffer("Transform", 0, *m_ubo);
        auto transform = static_cast<Transform*>(m_ubo->map());
        *transform = m_transform;
        m_ubo->unmap();
        m_ubo->unbind();

        if(m_mesh != nullptr)
            m_mesh->render();
    }
}
