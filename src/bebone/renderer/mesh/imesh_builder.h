#ifndef _BEBONE_RENDERER_IMESH_BUILDER_H_
#define _BEBONE_RENDERER_IMESH_BUILDER_H_

#include "../renderer_backend.h"
#include "../vertex_triangle.h"

#include "imesh.h"

namespace bebone::renderer {
    class IMeshBuilder {
        private:

        public:
            virtual void append_triangle(const VertexTriangle& triangle);
            virtual void append_triangles(const VertexTriangle* triangles, const u64& count);

            virtual void append_vertex(const Vertex& vertex);
            virtual void append_vertices(const Vertex* vertices, const u64& count);

            virtual std::shared_ptr<IMesh> build();
    };
}

#endif
