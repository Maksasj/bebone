#ifndef _BEBONE_GFX_VULKAN_RENDER_PASS_H_
#define _BEBONE_GFX_VULKAN_RENDER_PASS_H_

#include "../gfx_backend.h"

#include "vulkan_device.h"

namespace bebone::gfx {
    class VulkanRenderPass {
        public:
            VkRenderPass renderPass;

            VulkanRenderPass(VulkanDevice& _device, VkFormat colorAttachmentImageFormat);
            ~VulkanRenderPass();

            VkFormat find_depth_format(VulkanDevice& device);
    };
}

#endif
