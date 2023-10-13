#include "renderer.h"

namespace game::core {
    Renderer::Renderer(std::shared_ptr<GLShaderProgram>& shaderProgram, shared_ptr<OrthographicCamera>& camera) : camera(camera) {
        this->shaderProgram = shaderProgram;

        vao = make_shared<GLVertexArrayObject>();

        vector<f32> vertices = {
            -1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            -1.0f, -1.0f, 0.0f, 0.0f,

            -1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 0.0f
        };

        vao->bind();
            vba = make_shared<GLVertexBufferObject>(vertices);
            vao->link_attributes(*vba, 0, 4, GL_FLOAT, 4 * sizeof(float), (void*)0);
        vba->unbind();

        matricesUbo = make_shared<GLUniformBufferObject>(sizeof(ShaderMatrices));
    }

    Renderer::~Renderer() {
        vao->destroy();
        vao = nullptr;

        matricesUbo->destroy();
        shaderProgram->destroy();
    }

    void Renderer::render(GLTexture& texture, const Transform& transform) {
        shaderProgram->enable();

        const Vec3f& position = transform.get_position();
        const f32& scale = transform.get_scale();

        static float f = 0.0f;

        Mat4f model = Mat4f::identity();
        model = model * model.scale(0.25);
        model = model * omni::types::trait_bryan_angle_yxz(Vec3f(0.0f, 0.0f, f));
        model = model * model.translation(position);

        f += 0.01f;

        matricesUbo->bind();
        shaderProgram->bind_buffer("Matrices", 0, *matricesUbo);
        auto matricesPtr = static_cast<ShaderMatrices*>(matricesUbo->map());
        matricesPtr->model = model;
        matricesPtr->projection = camera->get_projection_matrix();
        matricesUbo->unmap();
        matricesUbo->unbind();

        texture.bind();

        vao->bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        vao->unbind();
    }
}