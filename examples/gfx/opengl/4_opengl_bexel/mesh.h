#ifndef BEXEL_MESH_H
#define BEXEL_MESH_H

#include <vector>
#include <memory>

#include "vertex.h"

namespace bexel {
    class Mesh : private core::NonCopyable {
        private:
            vector<Vertex> m_vertices;
            vector<u32> m_indices;

            unique_ptr<GLVertexArrayObject> m_vao;
            unique_ptr<GLVertexBufferObject> m_vbo;
            unique_ptr<GLElementBufferObject> m_ebo;

        public:
            Mesh(const vector<Vertex>& vertices, const vector<u32>& indices) : m_vertices(vertices), m_indices(indices) {
                m_vao = make_unique<GLVertexArrayObject>();
                m_vao->bind();

                m_vbo = make_unique<GLVertexBufferObject>(m_vertices.data(), m_vertices.size() * sizeof(Vertex));
                m_ebo = make_unique<GLElementBufferObject>(m_indices);

                m_vao->link_attributes(*m_vbo, 0, 3, GL_FLOAT, 6 * (sizeof(float)), (void*)0);
                m_vao->link_attributes(*m_vbo, 1, 3, GL_FLOAT, 6 * (sizeof(float)), (void*)(3 * sizeof(float)));

                m_vao->unbind();
                m_vbo->unbind();
                m_ebo->unbind();
            }

            void draw() const {
                m_vao->bind();
                glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
            }
    };
}


#endif
