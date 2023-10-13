#ifndef _RENDERER_H_
#define _RENDERER_H_

#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
#define OMNI_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"
#include "transform.h"
#include "orthographic_camera.h"

using namespace bebone::gfx::opengl;

namespace game::core {
    class Renderer {
        private:
            struct ShaderMatrices {
                Mat4f model;
                Mat4f projection;
            };

            GLShaderProgram shaderProgram;
            GLVertexArrayObject vao;
            GLUniformBufferObject matricesUbo;

            OrthographicCamera& camera;
        public:
            Renderer(GLShaderProgram& shaderProgram, OrthographicCamera& camera);
            ~Renderer();

            void render(GLTexture& texture, const Transform& transform);
    };
}

#endif
