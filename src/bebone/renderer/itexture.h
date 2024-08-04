#ifndef _BEBONE_RENDERER_ITEXTURE_H_
#define _BEBONE_RENDERER_ITEXTURE_H_

#include "renderer_backend.h"

namespace bebone::renderer {
    using namespace bebone::core;

    enum class TextureHandle : u32 { Invalid = 0 };

    class ITexture : public NonCopyable {
        public:
            virtual ~ITexture() = default;

            virtual TextureHandle get_handle() const = 0;
    };
}

#endif
