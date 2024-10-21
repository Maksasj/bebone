#ifndef _BEBONE_RENDERER_ITEXTURE_H_
#define _BEBONE_RENDERER_ITEXTURE_H_

#include "itexture_impl.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class ITexture : private NonCopyable {
        private:
            std::shared_ptr<ITextureImpl> impl;

        public:
            ITexture(const std::shared_ptr<ITextureImpl>& impl);

            [[nodiscard]] TextureHandle get_handle() const;
            std::shared_ptr<ITextureImpl> get_impl() const;
    };
}

#endif
