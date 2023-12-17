#include "batch.h"

namespace game::core {
    Batch::Batch(shared_ptr<GLShaderProgram>& shaderProgram, shared_ptr<OrthographicCamera>& camera, const size_t& quadLimit) :
        camera(camera), shaderProgram(shaderProgram), cachedTextureUnits(map<shared_ptr<GLTexture>, int>()), texturesToDraw(vector<shared_ptr<GLTexture>>()), currentTextureUnitIndex(0), indicesSize(0), quadSize(0) {
        
        textureUnitCapacity = min({GLGpuProperties::texture_unit_capacity(), MAX_TEXTURE_UNITS});

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

    void Batch::add(const shared_ptr<GameObject>& gameObject, const shared_ptr<SpriteRenderer>& renderer) {
        gameObjectsToDraw[gameObject] = renderer;
    }

    void Batch::add_indices() {
        unsigned int indices[6];
        size_t totalVerticesSize = quadSize * 4;

        indices[0] = totalVerticesSize - 4;
        indices[1] = totalVerticesSize - 3;
        indices[2] = totalVerticesSize - 1;

        indices[3] = totalVerticesSize - 3;
        indices[4] = totalVerticesSize - 2;
        indices[5] = totalVerticesSize - 1;

        ebo->buffer_sub_data(indicesSize * sizeof(unsigned int), sizeof(indices), indices);

        indicesSize += 6;
    }

    bool Batch::try_cache_texture(const shared_ptr<GLTexture>& texture) {
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
        upload_textures();

        shaderProgram->enable();

        Mat4f model = Mat4f::identity();
        model = model * model.scale(1.0f);
        model = model * omni::types::trait_bryan_angle_yxz(Vec3f(0.0f, 0.0f, 0.0f));
        model = model * model.translation(Vec3f(0.0f, 0.0f, 0.0f));

        for (auto texture : texturesToDraw) {
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

    void Batch::upload_textures() {
        for (auto it = gameObjectsToDraw.begin(); it != gameObjectsToDraw.end(); ++it) {
            auto gameObject = it->first;
            auto renderer = it->second;

            auto transform = gameObject->get_transform();
            auto sprite = renderer->get_sprite();
            auto texture = sprite->get_texture();

            if (!try_cache_texture(texture)) {
                continue;
            }

            auto quad = create_quad(sprite, transform, cachedTextureUnits[texture]);
            size_t verticesSize = quad.size() * sizeof(ShaderVertex);

            vbo->buffer_sub_data(quadSize * verticesSize, verticesSize, quad.data());
            ++quadSize;

            add_indices();
        }
    }

    array<ShaderVertex, 4> Batch::create_quad(const shared_ptr<Sprite>& sprite, const Transform& transform, const int& textureUnit) {
        Vec3f position = transform.get_position();
        f32 scale = transform.get_scale();
        float width = sprite->get_width() * scale / PIXELS_PER_UNIT;
        float height = sprite->get_height() * scale / PIXELS_PER_UNIT;

        ShaderVertex v0;
        v0.position = { position.x - width, position.y - height };
        v0.textureCoordinates = { 0.0f, 0.0f };
        v0.textureUnit = textureUnit;

        ShaderVertex v1;
        v1.position = { position.x - width, position.y + height };
        v1.textureCoordinates = { 0.0f, 1.0f };
        v1.textureUnit = textureUnit;

        ShaderVertex v2;
        v2.position = { position.x + width, position.y + height };
        v2.textureCoordinates = { 1.0f, 1.0f };
        v2.textureUnit = textureUnit;

        ShaderVertex v3;
        v3.position = { position.x + width, position.y - height };
        v3.textureCoordinates = { 1.0f, 0.0f };
        v3.textureUnit = textureUnit;

        return { v0, v1, v2, v3 };
    }
}