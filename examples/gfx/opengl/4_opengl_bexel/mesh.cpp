#include "mesh.h"

namespace bexel {
    Mesh::Mesh(const vector<Vertex>& vertices, const vector<u32>& indices) : m_vertices(vertices), m_indices(indices) {
        m_vao = make_unique<GLVertexArrayObject>();
        m_vao->bind();

        m_vbo = make_unique<GLVertexBufferObject>(m_vertices.data(), m_vertices.size() * sizeof(Vertex));
        m_ebo = make_unique<GLElementBufferObject>(m_indices);

        m_vao->link_attributes(*m_vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, pos));
        m_vao->link_attributes(*m_vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, color));

        m_vao->unbind();
        m_vbo->unbind();
        m_ebo->unbind();
    }

    void Mesh::render() const {
        m_vao->bind();
        glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
    }
}
