#ifndef _BEBONE_GFX_VULKAN_RENDER_PASS_H_
#define _BEBONE_GFX_VULKAN_RENDER_PASS_H_

#include "vulkan/vulkan_device.h"
#include "gfx_backend.h"

namespace bebone::gfx {
    class VulkanRenderPass {
        public:
            VulkanDevice& device;
            VkRenderPass renderPass;

            VulkanRenderPass(VulkanDevice& _device, VkFormat colorAttachmentImageFormat);
            ~VulkanRenderPass();

            VkFormat find_depth_format();
    };
}

#endif
