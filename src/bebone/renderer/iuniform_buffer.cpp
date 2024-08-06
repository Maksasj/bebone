#include "iuniform_buffer.h"

namespace bebone::renderer {
    using namespace bebone::core;

    IUniformBuffer::IUniformBuffer(const std::shared_ptr<IUniformBufferImpl>& impl) : impl(impl) {

    }

    void IUniformBuffer::upload_data(void* src, const size_t& size) {
        impl->upload_data(src, size);
    }
}
