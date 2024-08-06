#ifndef _BEBONE_RENDERER_VULKAN_UNIFORM_BUFFER_IMPL_H_
#define _BEBONE_RENDERER_VULKAN_UNIFORM_BUFFER_IMPL_H_

#include "iuniform_buffer_impl.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanUniformBufferImpl : public IUniformBufferImpl {
        private:
            std::vector<std::shared_ptr<VulkanBufferMemoryTuple>> buffers;
            std::vector<VulkanBindlessBufferHandle> handles;
        public:
            VulkanUniformBufferImpl(
                std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<VulkanPipelineManager>& pipeline_manager,
                const size_t& size);

            void upload_data(void* src, const size_t& size) override;

            [[nodiscard]] const std::vector<VulkanBindlessBufferHandle>& get_handles() const;
    };
}

#endif
