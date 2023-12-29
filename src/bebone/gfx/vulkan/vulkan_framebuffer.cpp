#include "vulkan_framebuffer.h"

#include "vulkan_device.h"
#include "vulkan_image_view.h"
#include "vulkan_render_pass.h"

namespace bebone::gfx::vulkan {
    using namespace bebone::core;

    VulkanFramebuffer::VulkanFramebuffer(VulkanDevice& device, std::vector<std::shared_ptr<VulkanImageView>>& attachmentViews, std::shared_ptr<VulkanRenderPass>& renderPass, VkExtent2D extent) {
        std::vector<VkImageView> attachments;
        for(auto& view : attachmentViews)
            attachments.push_back(view->backend);

        VkFramebufferCreateInfo framebufferInfo = {};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = renderPass->backend;
        framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        framebufferInfo.pAttachments = attachments.data();
        framebufferInfo.width = extent.width;
        framebufferInfo.height = extent.height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(device.device(), &framebufferInfo, nullptr, &backend) != VK_SUCCESS) {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }

    void VulkanFramebuffer::destroy(VulkanDevice &device) {
        vkDestroyFramebuffer(device.device(), backend, nullptr);
    }
}
