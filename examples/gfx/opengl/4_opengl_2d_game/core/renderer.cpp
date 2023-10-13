#include "renderer.h"

namespace game::core {
    Renderer::Renderer(GLShaderProgram& shaderProgram) : shaderProgram(shaderProgram) {
        GLVertexBufferObject vbo({
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 
    
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f});

        vao.link_attributes(vbo, 0, 4, GL_FLOAT, 4 * sizeof(float), (void*)0);
    }
}