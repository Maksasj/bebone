#include "batch.h"

namespace game::core {
    Batch::Batch(shared_ptr<GLShaderProgram>& shaderProgram, shared_ptr<OrthographicCamera>& camera, const size_t& quadLimit) :
        camera(camera), shaderProgram(shaderProgram), cachedTextureUnits(std::map<std::shared_ptr<GLTexture>, int>()), texturesToDraw(std::vector<std::shared_ptr<GLTexture>>()), currentTextureUnitIndex(0), indicesSize(0), quadSize(0), quadLimit(quadLimit) {
        
        textureUnitCapacity = std::min({GLGpuProperties::texture_unit_capacity(), MAX_TEXTURE_UNITS});

        size_t indexLimit = quadLimit * 6;

        vao = make_shared<GLVertexArrayObject>();

        vao->bind();
            vbo = make_shared<GLVertexBufferObject>(nullptr, quadLimit * sizeof(ShaderVertex), GL_DYNAMIC_DRAW);
            ebo = make_shared<GLElementBufferObject>(nullptr, indexLimit * sizeof(unsigned int), GL_DYNAMIC_DRAW);

            vao->link_attributes(*vbo, 0, 2, GL_FLOAT, sizeof(ShaderVertex), (void*)offsetof(ShaderVertex, position));
            vao->link_attributes(*vbo, 1, 2, GL_FLOAT, sizeof(ShaderVertex), (void*)offsetof(ShaderVertex, textureCoordinates));
            vao->link_attributes(*vbo, 2, 1, GL_INT, sizeof(ShaderVertex), (void*)offsetof(ShaderVertex, textureUnit));
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

    void Batch::add(const std::shared_ptr<Sprite>& sprite, const Transform& transform) {
        if (quadSize + 1 >= quadLimit) {
            return;
        }

        auto texture = sprite->get_texture();

        if (!try_cache_texture(texture)) {
            return;
        }

        auto quad = create_quad(transform.get_position(), cachedTextureUnits[texture]);
        
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

    bool Batch::try_cache_texture(const std::shared_ptr<GLTexture>& texture) {
        if (currentTextureUnitIndex >= textureUnitCapacity) {
            return false;
        }

        if (cachedTextureUnits.find(texture) == cachedTextureUnits.end()) {
            cachedTextureUnits[texture] = currentTextureUnitIndex;
            ++currentTextureUnitIndex;

            texturesToDraw.push_back(texture);
        }

        return true;
    }

    void Batch::render() {
        shaderProgram->enable();

        Mat4f model = Mat4f::identity();
        model = model * model.scale(1.0f);
        model = model * omni::types::trait_bryan_angle_yxz(Vec3f(0.0f, 0.0f, 0.0f));
        model = model * model.translation(Vec3f(0.0f, 0.0f, 0.0f));
        
        for (auto texture : texturesToDraw) {
            texture->bind();
            texture->bind_texture_unit(cachedTextureUnits[texture]);
        }

        vao->bind();
            shaderProgram->set_uniform("u_Model", model);
            shaderProgram->set_uniform("u_Projection", camera->get_projection_matrix());
            shaderProgram->set_uniform("u_Textures", textureUnitCapacity, samplers);
            GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(indicesSize), GL_UNSIGNED_INT, nullptr);
        vao->unbind();

        quadSize = 0;
        indicesSize = 0;
        currentTextureUnitIndex = 0;
        cachedTextureUnits.clear();
        texturesToDraw.clear();
    }

    std::array<ShaderVertex, 4> Batch::create_quad(const Vec2f& position, const int& textureUnit) {
        f32 size = 0.5f;

        ShaderVertex v0;
        v0.position = { position.x - size, position.y - size };
        v0.textureCoordinates = { 0.0f, 0.0f };
        v0.textureUnit = textureUnit;

        ShaderVertex v1;
        v1.position = { position.x - size, position.y + size };
        v1.textureCoordinates = { 0.0f, 1.0f };
        v1.textureUnit = textureUnit;

        ShaderVertex v2;
        v2.position = { position.x + size, position.y + size };
        v2.textureCoordinates = { 1.0f, 1.0f };
        v2.textureUnit = textureUnit;

        ShaderVertex v3;
        v3.position = { position.x + size, position.y - size };
        v3.textureCoordinates = { 1.0f, 0.0f };
        v3.textureUnit = textureUnit;

        return { v0, v1, v2, v3 };
    }
}