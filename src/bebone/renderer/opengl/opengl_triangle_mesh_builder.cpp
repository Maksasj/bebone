#include "opengl_triangle_mesh_builder.h"

namespace bebone::renderer {
    OpenGLTriangleMeshBuilder::OpenGLTriangleMeshBuilder() : index_offset(0) {

    }

    void OpenGLTriangleMeshBuilder::append_triangle(const VertexTriangle& triangle) {
        vertices.push_back(triangle.vertices[0]);
        vertices.push_back(triangle.vertices[1]);
        vertices.push_back(triangle.vertices[2]);

        indices.push_back(index_offset + 0);
        indices.push_back(index_offset + 1);
        indices.push_back(index_offset + 2);

        index_offset += 3;
    }

    void OpenGLTriangleMeshBuilder::append_triangles(const VertexTriangle* triangles, const u64& count) {
        // Todo
        for(u64 i = 0; i < count; ++i)
            append_triangle(triangles[i]);
    }

    void OpenGLTriangleMeshBuilder::append_vertex(const Vertex& vertex) {
        vertices.push_back(vertex);
        indices.push_back(index_offset);
        ++index_offset;
    }

    void OpenGLTriangleMeshBuilder::append_vertices(const Vertex* verts, const u64& count) {
        // Todo
        for(u64 i = 0; i < count; ++i)
            append_vertex(verts[i]);
    }

    void OpenGLTriangleMeshBuilder::append_raw(const Vertex* verts, const u64& vert_count, const u32* inds, const u64& ind_count) {
        for(u64 i = 0; i < vert_count; ++i)
            vertices.push_back(verts[i]);

        for(u64 i = 0; i < ind_count; ++i)
            indices.push_back(inds[i]);
    }

    void OpenGLTriangleMeshBuilder::clear() {
        vertices.clear();
        indices.clear();
        index_offset = 0;
    }

    std::shared_ptr<IMesh> OpenGLTriangleMeshBuilder::build() {
        return std::make_shared<OpenGLTriangleMesh>(vertices, indices);
    }
}
