#include "batch.h"

namespace game::core {
    Batch::Batch(shared_ptr<GLShaderProgram>& shaderProgram, shared_ptr<OrthographicCamera>& camera, const size_t& quadLimit, shared_ptr<GLTexture>& texture) : camera(camera), shaderProgram(shaderProgram), size(0), quadLimit(quadLimit), texture(texture) {
        indexLimit = quadLimit * 6;

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

        texture->destroy();
        texture = nullptr;
    }

    void Batch::add(const Transform& transform) {
        //auto quad = create_quad(transform.get_position());

        std::vector<GLfloat> quad = {
            0.5f, 0.5f,     1.0f, 1.0f,
            0.5f, -0.5f,    1.0f, 0.0f,
            -0.5f, -0.5f,   0.0f, 0.0f,
            -0.5f, 0.5f,    0.0f, 1.0f
        };
        
        vbo->buffer_sub_data(size, quad.size() * sizeof(GLfloat), quad.data());
        //size += quad.size();

        add_indices();
    }

    void Batch::add_indices() {
        unsigned int indices[6];

        indices[0] = 0;
        indices[1] = 1;
        indices[2] = 3;

        indices[3] = 1;
        indices[4] = 2;
        indices[5] = 3;

        ebo->buffer_sub_data(0, sizeof(indices), indices);
    }

    void Batch::render() {
        shaderProgram->enable();

        //TODO: set uniforms

        // Mat4f model = Mat4f::identity();
        // model = model * model.scale(1.0f);
        // model = model * omni::types::trait_bryan_angle_yxz(Vec3f(0.0f, 0.0f, 0.0f));
        // model = model * model.translation(Vec3f(0.0f, 0.0f, 0.0f));
        
        texture->bind();
        vao->bind();
            // shaderProgram->set_uniform("model", model);
            // shaderProgram->set_uniform("projection", camera->get_projection_matrix());
            shaderProgram->set_uniform("image", 0);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        vao->unbind();
        texture->unbind();
        //size = 0;
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