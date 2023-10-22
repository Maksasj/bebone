#include "batch.h"

namespace game::core {
    Batch::Batch(shared_ptr<GLShaderProgram>& shaderProgram, shared_ptr<OrthographicCamera>& camera, const size_t& capacity) : camera(camera), CAPACITY(capacity), size(0) {
        this->shaderProgram = shaderProgram;

        vao = make_shared<GLVertexArrayObject>();

        vao->bind();
            vbo = make_shared<GLVertexBufferObject>(nullptr, capacity * sizeof(ShaderVertex), GL_DYNAMIC_DRAW);
            ebo = make_shared<GLElementBufferObject>(NULL, GL_DYNAMIC_DRAW);

            vao->link_attributes(*vbo, 0, 2, GL_FLOAT, sizeof(ShaderVertex), (void*)offsetof(ShaderVertex, position));
            vao->link_attributes(*vbo, 1, 2, GL_FLOAT, sizeof(ShaderVertex), (void*)offsetof(ShaderVertex, textureCoordinates));
        vao->unbind();

        matricesUbo = make_shared<GLUniformBufferObject>(sizeof(ShaderMatrices));
    }

    Batch::~Batch() {
        vao->destroy();
        vao = nullptr;

        vbo->destroy();
        vbo = nullptr;

        ebo->destroy();
        ebo = nullptr;

        matricesUbo->destroy();
        matricesUbo = nullptr;

        shaderProgram->destroy();
        shaderProgram = nullptr;
    }

    void Batch::add(const Transform& transform) {
        auto quad = create_quad(transform.get_position());
        vbo->buffer_sub_data(size, quad.size(), quad.data());
        size += quad.size();

        add_indices();
    }

    void Batch::add_indices() {
        uint32_t indices[6];

        indices[0] = size - 4;
        indices[1] = size - 3;
        indices[2] = size - 2;

        indices[3] = size - 2;
        indices[4] = size - 1;
        indices[4] = size - 4;

        ebo->buffer_sub_data(size - 4, 6, indices);
    }

    void Batch::render() {
        vao->bind();
        glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
        vao->unbind();

        size = 0;
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