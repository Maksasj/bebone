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
            shared_ptr<OrthographicCamera> camera;

            shared_ptr<GLShaderProgram> shaderProgram;

            shared_ptr<GLVertexArrayObject> vao;
            shared_ptr<GLVertexBufferObject> vbo;
            shared_ptr<GLElementBufferObject> ebo;

            size_t indicesSize;
            size_t quadSize;
            size_t quadLimit;

            shared_ptr<GLTexture> texture;

            array<ShaderVertex, 4> create_quad(const Vec2f& position);
            void add_indices();

        public:
            Batch(shared_ptr<GLShaderProgram>& shaderProgram, shared_ptr<OrthographicCamera>& camera, const size_t& quadLimit, shared_ptr<GLTexture>& texture);
            ~Batch();

            void add(const Transform& transform);
            void render();
    };
}

#endif
