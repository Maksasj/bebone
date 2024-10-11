#ifndef _BEBONE_GFX_VULKAN_FRAMEBUFFER_H_
#define _BEBONE_GFX_VULKAN_FRAMEBUFFER_H_

#include <vector>

#include "../gfx_backend.h"

#include "interface/i_vulkan_device.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanDevice;

    class IVulkanImageView;
    class VulkanRenderPass;

    class VulkanFramebuffer : private core::NonCopyable {
        public:
            VkFramebuffer framebuffer;

        private:
            IVulkanDevice& device_owner;

        public:
            VulkanFramebuffer(
                IVulkanDevice& device,
                std::vector<std::unique_ptr<IVulkanImageView>>& attachment_views,
                std::unique_ptr<VulkanRenderPass>& render_pass,
                VkExtent2D extent);

            ~VulkanFramebuffer();
    };
}

#endif
