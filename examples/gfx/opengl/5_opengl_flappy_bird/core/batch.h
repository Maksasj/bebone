#ifndef _BATCH_H_
#define _BATCH_H_

#include "bebone/bebone.h"
#include <memory>
#include <vector>
#include <map>

#include "orthographic_camera.h"
#include "sprite.h"
#include "shader_vertex.h"

#include "entity_component_system/game_object.h"
#include "entity_component_system/transform.h"
#include "entity_component_system/components/sprite_renderer.h"

namespace game::core {
    using namespace bebone::core;
    using namespace std;
    using namespace bebone::gfx::opengl;
    using namespace ecs;
    
    class Batch : private NonCopyable {
        private:
            shared_ptr<OrthographicCamera> camera;

            shared_ptr<GLShaderProgram> shaderProgram;

            shared_ptr<GLVertexArrayObject> vao;
            shared_ptr<GLVertexBufferObject> vbo;
            shared_ptr<GLElementBufferObject> ebo;

            const unsigned int PIXELS_PER_UNIT = 32;

            const int MAX_TEXTURE_UNITS = 32;
            int textureUnitCapacity;
            int samplers[32] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};

            map<shared_ptr<GLTexture>, int> cachedTextureUnits;
            vector<shared_ptr<GLTexture>> texturesToDraw;
            int currentTextureUnitIndex;

            size_t indicesSize;
            size_t quadSize;

            map<shared_ptr<GameObject>, shared_ptr<SpriteRenderer>> gameObjectsToDraw;

            array<ShaderVertex, 4> create_quad(const shared_ptr<Sprite>& sprite, const Transform& transform, const int& textureUnit);
            void add_indices();
            void upload_textures();
            bool try_cache_texture(const shared_ptr<GLTexture>& texture);
        public:
            Batch(shared_ptr<GLShaderProgram>& shaderProgram, shared_ptr<OrthographicCamera>& camera, const size_t& quadLimit);
            ~Batch();

            void add(const shared_ptr<GameObject>& gameObject, const shared_ptr<SpriteRenderer>& renderer);
            void render();
    };
}

#endif
