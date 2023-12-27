#ifndef _BEBONE_GFX_VULKAN_FRAMEBUFFER_H_
#define _BEBONE_GFX_VULKAN_FRAMEBUFFER_H_

#include <vector>

#include "../../core/core.h"
#include "../gfx_backend.h"

#include "vulkan_wrapper.tpp"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanDevice;

    class VulkanImageView;
    class VulkanRenderPass;

    class VulkanFramebuffer : public VulkanWrapper<VkFramebuffer>, private core::NonCopyable {
        public:
            VulkanFramebuffer(
                VulkanDevice& device,
                std::vector<std::shared_ptr<VulkanImageView>>& attachmentViews,
                std::shared_ptr<VulkanRenderPass>& renderPass,
                VkExtent2D extent);

            void destroy(VulkanDevice &device) override;
    };
}

#endif
