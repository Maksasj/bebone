#ifndef _BATCH_H_
#define _BATCH_H_

#include "bebone/bebone.h"
#include <memory>
#include <vector>

#include "orthographic_camera.h"
#include "sprite.h"
#include "transform.h"
#include "shader_vertex.h"

namespace game::core {
    using namespace bebone::core;
    using namespace std;
    using namespace bebone::gfx::opengl;
    
    class Batch : private NonCopyable {
        private:
            struct ShaderMatrices {
                Mat4f model;
                Mat4f projection;
            };

            shared_ptr<OrthographicCamera> camera;

            shared_ptr<GLShaderProgram> shaderProgram;

            shared_ptr<GLVertexArrayObject> vao;
            shared_ptr<GLVertexBufferObject> vbo;
            shared_ptr<GLElementBufferObject> ebo;
            shared_ptr<GLUniformBufferObject> matricesUbo;

            const int CAPACITY;
            size_t size;

            array<ShaderVertex, 4> create_quad(const Vec2f& position);
            void add_indices();
        public:
            Batch(shared_ptr<GLShaderProgram>& shaderProgram, shared_ptr<OrthographicCamera>& camera, const size_t& capacity);
            ~Batch();

            void add(const Transform& transform);
            void render();
    };
}

#endif
