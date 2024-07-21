#include "batch.h"

namespace game::core {
    Batch::Batch(shared_ptr<GLShaderProgram>& shader_program, shared_ptr<OrthographicCamera>& camera, const size_t& quad_limit) :
            camera(camera), shader_program(shader_program), cached_texture_units(map<shared_ptr<GLTexture2D>, int>()), textures_to_draw(vector<shared_ptr<GLTexture2D>>()), current_texture_unit_index(0), indices_size(0), quad_size(0), quad_limit(quad_limit) {

        texture_unit_capacity = min({GLGpuProperties::texture_unit_capacity(), max_texture_units});

        size_t index_limit = quad_limit * 6;
        size_t vertex_limit = quad_limit * 4;

        vao = make_shared<GLVertexArrayObject>();

        vao->bind();
            vbo = make_shared<GLVertexBufferObject>(nullptr, vertex_limit * sizeof(ShaderVertex), GL_DYNAMIC_DRAW);
            ebo = make_shared<GLElementBufferObject>(nullptr, index_limit * sizeof(u32), GL_DYNAMIC_DRAW);

            vao->link_attributes(*vbo, 0, 3, GL_FLOAT, sizeof(ShaderVertex), (void*)offsetof(ShaderVertex, position));
            vao->link_attributes(*vbo, 1, 2, GL_FLOAT, sizeof(ShaderVertex), (void*)offsetof(ShaderVertex, texture_coordinates));
            vao->link_attributes(*vbo, 2, 1, GL_INT, sizeof(ShaderVertex), (void*)offsetof(ShaderVertex, texture_unit));
        vao->unbind();
        vbo->unbind();
        ebo->unbind();

        #ifdef BATCH_DEBUG
        draw_calls = 0;
        #endif
    }

    Batch::~Batch() {
        vao->destroy();
        vao = nullptr;

        vbo->destroy();
        vbo = nullptr;

        ebo->destroy();
        ebo = nullptr;

        shader_program->destroy();
        shader_program = nullptr;
    }

    void Batch::add(const shared_ptr<GameObject>& game_object) {
        if (game_objects_to_draw.find(game_object) == game_objects_to_draw.end()) {
            auto renderer = game_object->get_component<SpriteRenderer>();
            if (renderer != nullptr) {
                game_objects_to_draw[game_object] = renderer;
            } else {
                cout << game_object->get_name() << " does not have a SpriteRenderer!";
            }
        }
    }

    void Batch::remove(const shared_ptr<GameObject>& game_object) {
        game_objects_to_draw.erase(game_object);
    }

    void Batch::render() {
        game_objects_to_draw_iterator = game_objects_to_draw.begin();

        #ifdef BATCH_DEBUG
        draw_calls = 0;
        #endif

        while (game_objects_to_draw_iterator != game_objects_to_draw.end()) {
            upload_textures();

            shader_program->enable();

            for (const auto& texture : textures_to_draw) {
                texture->bind_texture_unit(cached_texture_units[texture]);
            }

            vao->bind();
                shader_program->set_uniform("u_Projection", camera->get_projection_matrix());
                shader_program->set_uniform("u_Textures", texture_unit_capacity, samplers);
                GLContext::draw_elements(GL_TRIANGLES, static_cast<i32>(indices_size), GL_UNSIGNED_INT, nullptr);
            vao->unbind();

            quad_size = 0;
            indices_size = 0;
            current_texture_unit_index = 0;
            cached_texture_units.clear();
            textures_to_draw.clear();

            #ifdef BATCH_DEBUG
            ++draw_calls;
            #endif
        }
    }

    void Batch::upload_textures() {
        while (game_objects_to_draw_iterator != game_objects_to_draw.end()) {
            if (quad_size + 1 > quad_limit) {
                return;
            }

            auto game_object = game_objects_to_draw_iterator->first;
            auto renderer = game_objects_to_draw_iterator->second;

            auto transform = game_object->get_transform();
            auto sprite = renderer->get_sprite();
            auto texture = sprite->get_texture();

            if (!try_cache_texture(texture)) {
                return;
            }

            auto quad = create_quad(sprite, transform, cached_texture_units[texture]);
            size_t vertices_size = quad.size() * sizeof(ShaderVertex);

            vbo->buffer_sub_data(quad_size * vertices_size, vertices_size, quad.data());
            ++quad_size;

            add_indices();
            ++game_objects_to_draw_iterator;
        }
    }

    bool Batch::try_cache_texture(const shared_ptr<GLTexture2D>& texture) {
        if (current_texture_unit_index >= texture_unit_capacity) {
            return false;
        }

        if (cached_texture_units.find(texture) == cached_texture_units.end()) {
            cached_texture_units[texture] = current_texture_unit_index;
            ++current_texture_unit_index;

            textures_to_draw.push_back(texture);
        }

        return true;
    }

    array<ShaderVertex, 4> Batch::create_quad(const shared_ptr<Sprite>& sprite, const shared_ptr<Transform>& transform, const int& texture_unit) {
        Vec3f position = transform->get_position();
        f32 scale = transform->get_scale();
        f32 rotation = transform->get_rotation();

        float width = sprite->get_unit_width() * scale;
        float height = sprite->get_unit_height() * scale;
        Vec2f tmp;

        ShaderVertex v0;
        tmp = rotate_vertex({-width, -height}, rotation);
        v0.position = Vec3f(position.x + tmp.x, position.y + tmp.y, position.z);
        v0.texture_coordinates = {0.0f, 0.0f };
        v0.texture_unit = texture_unit;

        ShaderVertex v1;
        tmp = rotate_vertex({-width, height}, rotation);
        v1.position = Vec3f(position.x + tmp.x, position.y + tmp.y, position.z);
        v1.texture_coordinates = {0.0f, 1.0f };
        v1.texture_unit = texture_unit;

        ShaderVertex v2;
        tmp = rotate_vertex({width, height}, rotation);
        v2.position = Vec3f(position.x + tmp.x, position.y + tmp.y, position.z);
        v2.texture_coordinates = {1.0f, 1.0f };
        v2.texture_unit = texture_unit;

        ShaderVertex v3;
        tmp = rotate_vertex({width, -height}, rotation);
        v3.position = Vec3f(position.x + tmp.x, position.y + tmp.y, position.z);
        v3.texture_coordinates = {1.0f, 0.0f };
        v3.texture_unit = texture_unit;

        return { v0, v1, v2, v3 };
    }

    Vec2f Batch::rotate_vertex(const Vec2f& v, const f32& angle) const {
        Vec2f new_v = v;
        
        double radian = Math::deg_to_rad(angle);
        new_v.x = v.x * cos(radian) - v.y * sin(radian);
        new_v.y = v.x * sin(radian) + v.y * cos(radian);
        return new_v;
    }

    void Batch::add_indices() {
        unsigned int indices[6];
        size_t total_vertices_size = quad_size * 4;

        indices[0] = total_vertices_size - 4;
        indices[1] = total_vertices_size - 3;
        indices[2] = total_vertices_size - 1;

        indices[3] = total_vertices_size - 3;
        indices[4] = total_vertices_size - 2;
        indices[5] = total_vertices_size - 1;

        ebo->buffer_sub_data(indices_size * sizeof(unsigned int), sizeof(indices), indices);

        indices_size += 6;
    }

#pragma region debug
    #ifdef BATCH_DEBUG
    size_t Batch::get_draw_call_count() const {
        return draw_calls;
    }
    #endif
#pragma endregion
}