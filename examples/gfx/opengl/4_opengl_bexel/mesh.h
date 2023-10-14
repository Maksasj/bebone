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
            Mesh(const vector<Vertex>& vertices, const vector<u32>& indices);

            void render() const;
    };
}


#endif
