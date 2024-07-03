#ifndef BEXEL_MESH_H
#define BEXEL_MESH_H

#include <vector>
#include <memory>

#include "vertex.h"

namespace bexel {
    using namespace bebone;

    class Mesh final : private core::NonCopyable {
        private:
            vector<Vertex> vertices;
            vector<u32> indices;

            unique_ptr<GLVertexArrayObject> vao;
            unique_ptr<GLVertexBufferObject> vbo;
            unique_ptr<GLElementBufferObject> ebo;

        public:
            Mesh(const vector<Vertex>& vertices, const vector<u32>& indices);

            void render() const;
    };
}


#endif
