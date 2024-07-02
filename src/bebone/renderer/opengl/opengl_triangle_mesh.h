#ifndef _BEBONE_RENDERER_OPENGL_TRIANGLE_MESH_H_
#define _BEBONE_RENDERER_OPENGL_TRIANGLE_MESH_H_

#include "../renderer_backend.h"
#include "../mesh/imesh.h"
#include "../vertex.h"

namespace bebone::renderer {
    using namespace bebone::gfx::opengl;

    class OpenGLTriangleMesh : public IMesh {
        private:
            u64 indices_count;

        protected:
            unique_ptr<GLVertexArrayObject> vao;
            unique_ptr<GLVertexBufferObject> vbo;
            unique_ptr<GLElementBufferObject> ebo;

        public:
            OpenGLTriangleMesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indices);
            ~OpenGLTriangleMesh() override;

            u64 triangle_count() const override;
            u64 vertex_count() const override;

            void bind() override;
    };
}

#endif


