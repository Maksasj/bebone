#include "vulkan_uniform_buffer_impl.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanUniformBufferImpl::VulkanUniformBufferImpl(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanPipelineManager>& pipeline_manager,
        const size_t& size
    ) : device(device) {
        buffer = device->create_buffer_memory(size);
        handle  = pipeline_manager->bind_uniform_buffer(this->device, buffer);
    }

    void VulkanUniformBufferImpl::upload_data(void* src, const size_t& size) {
        buffer->upload_data(device, src, size);
    }

    UniformBufferHandle VulkanUniformBufferImpl::get_handle() {
        return static_cast<UniformBufferHandle>(handle);
    }
}
