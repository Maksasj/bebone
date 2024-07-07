#include "opengl_triangle_mesh.h"

namespace bebone::renderer {
    OpenGLTriangleMesh::OpenGLTriangleMesh(
        const std::vector<Vertex>& vertices,
        const std::vector<u32>& indices
    ) : indices_count(indices.size()) {

        vao = make_unique<GLVertexArrayObject>();
        vao->bind();

        vbo = make_unique<GLVertexBufferObject>(vertices.data(), vertices.size() * sizeof(Vertex));
        ebo = make_unique<GLElementBufferObject>(indices.data(), indices.size() * sizeof(u32));

        vao->link_attributes(*vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, position));
        vao->link_attributes(*vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, normal));
        vao->link_attributes(*vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, texcoord));

        vao->unbind();
        vbo->unbind();
        ebo->unbind();
    }

    OpenGLTriangleMesh::~OpenGLTriangleMesh() {
        vao->destroy();
        vbo->destroy();
        ebo->destroy();
    }

    u64 OpenGLTriangleMesh::triangle_count() const {
        return indices_count;
    }

    u64 OpenGLTriangleMesh::vertex_count() const {
        return indices_count * 3;
    }

    void OpenGLTriangleMesh::bind(ICommandEncoder* encoder) {
        vao->bind();
    }
}
