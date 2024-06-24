#include "mesh.h"

namespace bexel {
    Mesh::Mesh(const vector<Vertex>& vertices, const vector<u32>& indices) : vertices(vertices), indices(indices) {
        vao = make_unique<GLVertexArrayObject>();
        vao->bind();

        vbo = make_unique<GLVertexBufferObject>(vertices.data(), vertices.size() * sizeof(Vertex));
        ebo = make_unique<GLElementBufferObject>(indices.data(), indices.size() * sizeof(u32));

        vao->link_attributes(*vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, pos));
        vao->link_attributes(*vbo, 1, 2, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, tex));

        vao->unbind();
        vbo->unbind();
        ebo->unbind();
    }

    void Mesh::render() const {
        vao->bind();

        GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(indices.size()), GL_UNSIGNED_INT, nullptr);
    }
}
