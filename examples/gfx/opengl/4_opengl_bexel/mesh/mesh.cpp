#include "mesh.h"

namespace bexel {
    Mesh::Mesh(const vector<Vertex>& vertices, const vector<u32>& indices) : m_vertices(vertices), m_indices(indices) {
        m_vao = make_unique<GLVertexArrayObject>();
        m_vao->bind();

        m_vbo = make_unique<GLVertexBufferObject>(m_vertices.data(), m_vertices.size() * sizeof(Vertex));
        m_ebo = make_unique<GLElementBufferObject>(m_indices.data(), m_indices.size() * sizeof(u32));

        m_vao->link_attributes(*m_vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, pos));
        m_vao->link_attributes(*m_vbo, 1, 2, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, tex));

        m_vao->unbind();
        m_vbo->unbind();
        m_ebo->unbind();
    }

    void Mesh::render() const {
        m_vao->bind();

        GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(m_indices.size()), GL_UNSIGNED_INT, nullptr);
    }
}
