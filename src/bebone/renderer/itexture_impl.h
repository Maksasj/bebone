#ifndef _BEBONE_RENDERER_ITEXTURE_IMPL_H_
#define _BEBONE_RENDERER_ITEXTURE_IMPL_H_

#include "renderer_backend.h"

namespace bebone::renderer {
    using namespace bebone::core;

    enum class TextureHandle : u32 { Invalid = 0 };

    class ITextureImpl : public NonCopyable {
        public:
            virtual ~ITextureImpl() = default;

            virtual TextureHandle get_handle() const = 0;
    };
}

#endif
