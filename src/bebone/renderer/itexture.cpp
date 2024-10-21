#include "itexture.h"

namespace bebone::renderer {
    using namespace bebone::core;

    ITexture::ITexture(const std::shared_ptr<ITextureImpl>& impl) : impl(impl) {

    }

    TextureHandle ITexture::get_handle() const {
        return impl->get_handle();
    }

    std::shared_ptr<ITextureImpl> ITexture::get_impl() const {
        return impl;
    }
}
