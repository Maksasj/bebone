#ifndef _BEBONE_RENDERER_ITEXTURE_MANAGER_H_
#define _BEBONE_RENDERER_ITEXTURE_MANAGER_H_

#include "renderer_backend.h"
#include "itexture_impl.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class ITextureManager : public NonCopyable {
        public:
            virtual ~ITextureManager() = default;

            // Todo
            virtual TextureHandle create_texture(const Vec2i& size) = 0;
            virtual TextureHandle create_depth_texture(const Vec2i& size) = 0;

            virtual TextureHandle load_texture(const std::string& file_path) = 0;

            virtual std::optional<std::shared_ptr<ITextureImpl>> get_texture(const TextureHandle& handle) const = 0;
    };
}

#endif
