#include "irender_target.h"

#include <utility>

namespace bebone::renderer {
    using namespace bebone::core;

    IRenderTarget::IRenderTarget(
        const std::shared_ptr<IRenderTargetImpl>& impl,
        std::string name
    ) : impl(impl), name(std::move(name)) {

    }

    std::shared_ptr<IRenderTargetImpl> IRenderTarget::get_impl() const {
        return impl;
    }

    std::string IRenderTarget::get_name() const {
        return name;
    }
}
