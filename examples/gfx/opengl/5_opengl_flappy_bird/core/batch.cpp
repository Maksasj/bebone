#include "batch.h"

namespace game::core {
    Batch::Batch(shared_ptr<GLShaderProgram>& shaderProgram, shared_ptr<OrthographicCamera>& camera, const size_t& quadLimit) :
        camera(camera), shaderProgram(shaderProgram), indicesSize(0), quadSize(0), quadLimit(quadLimit) {
        
        size_t indexLimit = quadLimit * 6;

        vao = make_shared<GLVertexArrayObject>();

        vao->bind();
            vbo = make_shared<GLVertexBufferObject>(nullptr, quadLimit * sizeof(ShaderVertex), GL_DYNAMIC_DRAW);
            ebo = make_shared<GLElementBufferObject>(nullptr, indexLimit * sizeof(unsigned int), GL_DYNAMIC_DRAW);

            vao->link_attributes(*vbo, 0, 2, GL_FLOAT, sizeof(ShaderVertex), (void*)offsetof(ShaderVertex, position));
            vao->link_attributes(*vbo, 1, 2, GL_FLOAT, sizeof(ShaderVertex), (void*)offsetof(ShaderVertex, textureCoordinates));
        vao->unbind();
        vbo->unbind();
        ebo->unbind();
    }

    Batch::~Batch() {
        vao->destroy();
        vao = nullptr;

        vbo->destroy();
        vbo = nullptr;

        ebo->destroy();
        ebo = nullptr;

        shaderProgram->destroy();
        shaderProgram = nullptr;
    }

    void Batch::add(const Transform& transform) {
        if (quadSize + 1 >= quadLimit) {
            return;
        }

        auto quad = create_quad(transform.get_position());
        
        vbo->buffer_sub_data(quadSize * sizeof(ShaderVertex), quad.size() * sizeof(ShaderVertex), quad.data());
        quadSize += quad.size();

        add_indices();
    }

    void Batch::add_indices() {
        unsigned int indices[6];

        indices[0] = quadSize - 4;
        indices[1] = quadSize - 3;
        indices[2] = quadSize - 1;

        indices[3] = quadSize - 3;
        indices[4] = quadSize - 2;
        indices[5] = quadSize - 1;

        ebo->buffer_sub_data(indicesSize * sizeof(unsigned int), sizeof(indices), indices);

        indicesSize += 6;
    }

    void Batch::render() {
        shaderProgram->enable();

        Mat4f model = Mat4f::identity();
        model = model * model.scale(1.0f);
        model = model * omni::types::trait_bryan_angle_yxz(Vec3f(0.0f, 0.0f, 0.0f));
        model = model * model.translation(Vec3f(0.0f, 0.0f, 0.0f));
        
        vao->bind();
            shaderProgram->set_uniform("model", model);
            shaderProgram->set_uniform("projection", camera->get_projection_matrix());
            shaderProgram->set_uniform("image", 0);
            GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(indicesSize), GL_UNSIGNED_INT, nullptr);
        vao->unbind();
        
        quadSize = 0;
        indicesSize = 0;
    }

    std::array<ShaderVertex, 4> Batch::create_quad(const Vec2f& position) {
        f32 size = 0.5f;

        ShaderVertex v0;
        v0.position = { position.x - size, position.y - size };
        v0.textureCoordinates = { 0.0f, 0.0f };

        ShaderVertex v1;
        v1.position = { position.x - size, position.y + size };
        v1.textureCoordinates = { 0.0f, 1.0f };

        ShaderVertex v2;
        v2.position = { position.x + size, position.y + size };
        v2.textureCoordinates = { 1.0f, 1.0f };

        ShaderVertex v3;
        v3.position = { position.x + size, position.y - size };
        v3.textureCoordinates = { 1.0f, 0.0f };

        return { v0, v1, v2, v3 };
    }
}