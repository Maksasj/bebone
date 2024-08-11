#ifndef _BEBONE_RENDERER_OPENGL_TRIANGLE_MESH_IMPL_H_
#define _BEBONE_RENDERER_OPENGL_TRIANGLE_MESH_IMPL_H_

#include "renderer_backend.h"
#include "imesh_impl.h"
#include "vertex.h"

namespace bebone::renderer {
        using namespace bebone::gfx;

        class OpenGLTriangleMeshImpl : public IMeshImpl {
            private:
                u64 indices_count;

            protected:
                unique_ptr<GLVertexArrayObject> vao;
                unique_ptr<GLVertexBufferObject> vbo;
                unique_ptr<GLElementBufferObject> ebo;

            public:
                OpenGLTriangleMeshImpl(const std::vector<Vertex>& vertices, const std::vector<u32>& indices);
                ~OpenGLTriangleMeshImpl() override;

                u64 triangle_count() const override;
                u64 vertex_count() const override;

                void bind(ICommandEncoder* encoder) override;
        };
}

#endif

