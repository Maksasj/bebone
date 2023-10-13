#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "bebone/bebone.h"
#include "transform.h"

using namespace bebone::gfx::opengl;

namespace game::core {
    class Renderer : private NonCopyable {
        private:
            GLShaderProgram shaderProgram;
            GLVertexArrayObject vao;
        public:
            Renderer(GLShaderProgram& shaderProgram);
            ~Renderer();

            void render(GLTexture& texture, Transform transform);
    };
}

#endif
