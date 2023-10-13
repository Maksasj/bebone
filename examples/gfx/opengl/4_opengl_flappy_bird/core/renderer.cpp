#include "renderer.h"

namespace game::core {
    Renderer::Renderer(std::shared_ptr<GLShaderProgram>& shaderProgram, OrthographicCamera& camera) : shaderProgram(shaderProgram), matricesUbo(sizeof(ShaderMatrices)), camera(camera) {
        GLVertexBufferObject vbo({
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 
    
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f});

        vao.link_attributes(vbo, 0, 4, GL_FLOAT, 4 * sizeof(float), (void*)0);

        shaderProgram->bind_buffer("Matrices", 0, matricesUbo);
    }

    Renderer::~Renderer() {
        vao.destroy();
        matricesUbo.destroy();
        shaderProgram->destroy();
    }

    void Renderer::render(GLTexture& texture, const Transform& transform) {
        shaderProgram->enable();

        const Vec3f& position = transform.get_position();
        const f32& scale = transform.get_scale();

        Mat4f model = Mat4f::translation(position);

        model.translation(Vec3f(0.5f * scale, 0.5f * scale, 0));
        model = model * omni::types::trait_bryan_angle_yxz(Vec3f(0.0f, 0.0f, 1.0f));
        model.translation(Vec3f(-0.5f * scale, -0.5f * scale, 0));

        model.scale(scale);

        matricesUbo.bind();
        auto matricesPtr = static_cast<ShaderMatrices*>(matricesUbo.map());
        matricesPtr->model = model;
        matricesPtr->projection = camera.get_projection_matrix();
        matricesUbo.unbind();

        //texture.bind();

        // vao.bind();
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        // vao.unbind();
    }
}