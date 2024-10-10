#ifndef _BEBONE_GFX_VULKAN_FRAMEBUFFER_H_
#define _BEBONE_GFX_VULKAN_FRAMEBUFFER_H_

#include <vector>

#include "../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanDevice;

    class IVulkanImageView;
    class VulkanRenderPass;

    class VulkanFramebuffer : private core::NonCopyable {
        public:
            VkFramebuffer backend;

        private:
            VulkanDevice& device_owner;

        public:
            VulkanFramebuffer(
                VulkanDevice& device,
                std::vector<std::unique_ptr<IVulkanImageView>>& attachment_views,
                std::unique_ptr<VulkanRenderPass>& render_pass,
                VkExtent2D extent);

            ~VulkanFramebuffer();

            // void destroy(VulkanDevice& device) override;
    };
}

#endif
