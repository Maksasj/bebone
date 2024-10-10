#ifndef _BEBONE_RENDERER_ITEXTURE_MANAGER_H_
#define _BEBONE_RENDERER_ITEXTURE_MANAGER_H_

#include "renderer_backend.h"
#include "itexture.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class ITextureManager : private NonCopyable {
        public:
            virtual ~ITextureManager() = default;

            virtual TextureHandle create_texture(const Vec2i& size) = 0;
            virtual TextureHandle create_depth_texture(const Vec2i& size) = 0;
            virtual TextureHandle load_texture(const std::string& file_path) = 0;

            virtual void delete_texture(const TextureHandle& handle) = 0;

            virtual std::optional<std::shared_ptr<ITexture>> get_texture(const TextureHandle& handle) const = 0;
    };
}

#endif
