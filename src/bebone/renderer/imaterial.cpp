#include "imaterial.h"

namespace bebone::renderer {
    using namespace bebone::core;

    IMaterial::IMaterial(const std::shared_ptr<IMaterialImpl>& impl) : impl(impl) {

    }

    const MaterialHandle& IMaterial::get_handle() const {
        return impl->get_handle();
    }
}
