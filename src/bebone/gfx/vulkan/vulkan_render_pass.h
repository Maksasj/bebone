#ifndef _BEBONE_GFX_VULKAN_RENDER_PASS_H_
#define _BEBONE_GFX_VULKAN_RENDER_PASS_H_

#include <array>

#include "../gfx_backend.h"

#include "vulkan_device.h"
#include "vulkan_wrapper.tpp"
#include "vulkan_attachment.h"

namespace bebone::gfx {
    class VulkanRenderPass : public VulkanWrapper<VkRenderPass> {
        public:
            VulkanRenderPass(VulkanDevice& device, const std::vector<VulkanAttachment>& attachments);

            void destroy(VulkanDevice& device) override;
    };
}

#endif
