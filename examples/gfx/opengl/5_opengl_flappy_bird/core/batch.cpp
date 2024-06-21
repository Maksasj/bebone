#include "batch.h"

namespace game::core {
    Batch::Batch(shared_ptr<GLShaderProgram>& shaderProgram, shared_ptr<OrthographicCamera>& camera, const size_t& quadLimit) :
        camera(camera), shaderProgram(shaderProgram), cachedTextureUnits(map<shared_ptr<GLTexture2D>, int>()), texturesToDraw(vector<shared_ptr<GLTexture2D>>()), currentTextureUnitIndex(0), indicesSize(0), quadSize(0), quadLimit(quadLimit) {
        
        textureUnitCapacity = min({GLGpuProperties::texture_unit_capacity(), MAX_TEXTURE_UNITS});

        size_t indexLimit = quadLimit * 6;
        size_t vertexLimit = quadLimit * 4;

        vao = make_shared<GLVertexArrayObject>();

        vao->bind();
            vbo = make_shared<GLVertexBufferObject>(nullptr, vertexLimit * sizeof(ShaderVertex), GL_DYNAMIC_DRAW);
            ebo = make_shared<GLElementBufferObject>(nullptr, indexLimit * sizeof(u32), GL_DYNAMIC_DRAW);

            vao->link_attributes(*vbo, 0, 3, GL_FLOAT, sizeof(ShaderVertex), (void*)offsetof(ShaderVertex, position));
            vao->link_attributes(*vbo, 1, 2, GL_FLOAT, sizeof(ShaderVertex), (void*)offsetof(ShaderVertex, textureCoordinates));
            vao->link_attributes(*vbo, 2, 1, GL_INT, sizeof(ShaderVertex), (void*)offsetof(ShaderVertex, textureUnit));
        vao->unbind();
        vbo->unbind();
        ebo->unbind();

        #ifdef BATCH_DEBUG
        drawCalls = 0;
        #endif
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

    void Batch::add(const shared_ptr<GameObject>& gameObject) {
        if (gameObjectsToDraw.find(gameObject) == gameObjectsToDraw.end()) {
            auto renderer = gameObject->get_component<SpriteRenderer>();
            if (renderer != nullptr) {
                gameObjectsToDraw[gameObject] = renderer;
            } else {
                cout << gameObject->get_name() << " does not have a SpriteRenderer!";
            }
        }
    }

    void Batch::remove(const shared_ptr<GameObject>& gameObject) {
        gameObjectsToDraw.erase(gameObject);
    }

    void Batch::render() {
        gameObjectsToDrawIterator = gameObjectsToDraw.begin();

        #ifdef BATCH_DEBUG
        drawCalls = 0;
        #endif

        while (gameObjectsToDrawIterator != gameObjectsToDraw.end()) {
            upload_textures();

            shaderProgram->enable();

            Mat4f model = Mat4f::identity();
            model = model * model.scale(1.0f);
            model = model * bebone::core::trait_bryan_angle_yxz(Vec3f(0.0f, 0.0f, 0.0f));
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

            #ifdef BATCH_DEBUG
            ++drawCalls;
            #endif
        }
    }

    void Batch::upload_textures() {
        while (gameObjectsToDrawIterator != gameObjectsToDraw.end()) {
            if (quadSize + 1 > quadLimit) {
                return;
            }

            auto gameObject = gameObjectsToDrawIterator->first;
            auto renderer = gameObjectsToDrawIterator->second;

            auto transform = gameObject->get_transform();
            auto sprite = renderer->get_sprite();
            auto texture = sprite->get_texture();

            if (!try_cache_texture(texture)) {
                return;
            }

            auto quad = create_quad(sprite, transform, cachedTextureUnits[texture]);
            size_t verticesSize = quad.size() * sizeof(ShaderVertex);

            vbo->buffer_sub_data(quadSize * verticesSize, verticesSize, quad.data());
            ++quadSize;

            add_indices();
            ++gameObjectsToDrawIterator;
        }
    }

    bool Batch::try_cache_texture(const shared_ptr<GLTexture2D>& texture) {
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

    array<ShaderVertex, 4> Batch::create_quad(const shared_ptr<Sprite>& sprite, const shared_ptr<Transform>& transform, const int& textureUnit) {
        Vec3f position = transform->get_position();
        f32 scale = transform->get_scale();
        f32 rotation = transform->get_rotation();

        float width = sprite->get_unit_width() * scale;
        float height = sprite->get_unit_height() * scale;
        Vec2f tmp;

        ShaderVertex v0;
        tmp = rotateVertex( {-width, -height}, rotation);
        v0.position = Vec3f(position.x + tmp.x, position.y + tmp.y, position.z);
        v0.textureCoordinates = { 0.0f, 0.0f };
        v0.textureUnit = textureUnit;

        ShaderVertex v1;
        tmp = rotateVertex( {-width, height}, rotation);
        v1.position = Vec3f(position.x + tmp.x, position.y + tmp.y, position.z);
        v1.textureCoordinates = { 0.0f, 1.0f };
        v1.textureUnit = textureUnit;

        ShaderVertex v2;
        tmp = rotateVertex( {width, height}, rotation);
        v2.position = Vec3f(position.x + tmp.x, position.y + tmp.y, position.z);
        v2.textureCoordinates = { 1.0f, 1.0f };
        v2.textureUnit = textureUnit;

        ShaderVertex v3;
        tmp = rotateVertex( {width, -height}, rotation);
        v3.position = Vec3f(position.x + tmp.x, position.y + tmp.y, position.z);
        v3.textureCoordinates = { 1.0f, 0.0f };
        v3.textureUnit = textureUnit;

        return { v0, v1, v2, v3 };
    }

    Vec2f Batch::rotateVertex(const Vec2f& v, const f32& angle) const {
        Vec2f newV = v;
        
        double radian = Math::deg_to_rad(angle);
        newV.x = v.x * cos(radian) - v.y * sin(radian);
        newV.y = v.x * sin(radian) + v.y * cos(radian);
        return newV;
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

#pragma region debug
    #ifdef BATCH_DEBUG
    size_t Batch::get_draw_call_count() const {
        return drawCalls;
    }
    #endif
#pragma endregion
}