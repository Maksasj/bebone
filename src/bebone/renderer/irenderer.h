#ifndef _BEBONE_RENDERER_I_RENDERER_H_
#define _BEBONE_RENDERER_I_RENDERER_H_

#include "../gfx/gfx.h"

namespace bebone::renderer {
    // Abstract classes
    class IProgram {}; // This is shader
    // class IRenderPass;

    class IUniformBuffer {};
    class IVertexBuffer {};
    class IIndexBuffer {};
    class ITexture {};

    class IMesh {};
    class IMaterial {};

    class ISprite {};
    class IModel {};

    // Handle types
    class ProgramHandle {};
    // class RenderPassHandle;

    class UniformBufferHandle {};
    class VertexBufferHandle {};
    class IndexBufferHandle {};
    class TextureHandle {};

    class MeshHandle {};
    class MaterialHandle {};

    class SpriteHandle {};
    class ModelHandle {};

    // Helper classes
    struct Vertex {};

    struct Transform {
        core::Vec3f pos;
    };

    class IRenderer {
        private:
            const GfxAPI api;

        public:
            explicit IRenderer(const GfxAPI& api);

            virtual ~IRenderer() = default;

            // Todo, implement
            virtual SpriteHandle load_sprite(const std::string& file_path) {};
            virtual ModelHandle load_model(const std::string& file_path) {};

            // Todo, implement
            virtual void render(const SpriteHandle&, const Transform& = {}) {};
            virtual void render(const ModelHandle&, const Transform& = {}) {};

            virtual void present() = 0;
    };
}

#endif
