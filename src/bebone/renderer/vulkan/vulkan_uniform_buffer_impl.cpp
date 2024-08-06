#include "vulkan_uniform_buffer_impl.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanUniformBufferImpl::VulkanUniformBufferImpl(
        std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanPipelineManager>& pipeline_manager,
        const size_t& size
    ) {
        buffers = device->create_buffer_memorys(size, 3);
        handles  = pipeline_manager->bind_uniform_buffers(device, buffers);
    }

    void VulkanUniformBufferImpl::upload_data(void* src, const size_t& size) {

    }

    const std::vector<VulkanBindlessBufferHandle>& VulkanUniformBufferImpl::get_handles() const {
        return handles;
    }
}
