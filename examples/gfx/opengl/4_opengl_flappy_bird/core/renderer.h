#ifndef _RENDERER_H_
#define _RENDERER_H_

#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
#define OMNI_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"
#include "transform.h"
#include "orthographic_camera.h"
#include "sprite.h"

#include <memory>

using namespace bebone::gfx::opengl;

namespace game::core {
    using namespace std;

    class Renderer : private NonCopyable {
        private:
            struct ShaderMatrices {
                Mat4f model;
                Mat4f projection;
            };

            shared_ptr<OrthographicCamera> camera;

            shared_ptr<GLShaderProgram> shaderProgram;

            shared_ptr<GLVertexArrayObject> vao;
            shared_ptr<GLVertexBufferObject> vbo;
            shared_ptr<GLUniformBufferObject> matricesUbo;

        public:
            Renderer(shared_ptr<GLShaderProgram>& shaderProgram, shared_ptr<OrthographicCamera>& camera);
            ~Renderer();

            void render(const Sprite& sprite, const Transform& transform);
    };
}

#endif
