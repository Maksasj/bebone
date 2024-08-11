#include "opengl_triangle_mesh_impl.h"

namespace bebone::renderer {
    OpenGLTriangleMeshImpl::OpenGLTriangleMeshImpl(
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

    OpenGLTriangleMeshImpl::~OpenGLTriangleMeshImpl() {
        vao->destroy();
        vbo->destroy();
        ebo->destroy();
    }

    u64 OpenGLTriangleMeshImpl::triangle_count() const {
        return indices_count;
    }

    u64 OpenGLTriangleMeshImpl::vertex_count() const {
        return indices_count * 3;
    }

    void OpenGLTriangleMeshImpl::bind(ICommandEncoder* encoder) {
        vao->bind();
    }
}