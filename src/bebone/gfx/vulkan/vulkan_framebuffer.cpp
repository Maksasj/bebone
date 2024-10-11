#include "vulkan_framebuffer.h"

#include "vulkan_device.h"
#include "vulkan_image_view.h"
#include "vulkan_render_pass.h"

namespace bebone::gfx {
    using namespace bebone::core;

    VulkanFramebuffer::VulkanFramebuffer(
        IVulkanDevice& device,
        std::vector<std::unique_ptr<IVulkanImageView>>& attachment_views,
        std::unique_ptr<VulkanRenderPass>& render_pass,
        VkExtent2D extent
    ) : device_owner(device) {
        auto attachments = std::vector<VkImageView> {};
        attachments.reserve(attachment_views.size());
        
        for(auto& view : attachment_views)
            attachments.push_back(view->get_vk_image_view());

        VkFramebufferCreateInfo create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        create_info.renderPass = render_pass->backend;
        create_info.attachmentCount = static_cast<uint32_t>(attachments.size());
        create_info.pAttachments = attachments.data();
        create_info.width = extent.width;
        create_info.height = extent.height;
        create_info.layers = 1;

        if(vkCreateFramebuffer(device_owner.get_vk_device(), &create_info, nullptr, &backend) != VK_SUCCESS) {
            LOG_ERROR("Failed to create framebuffer");
            throw std::runtime_error("failed to create framebuffer!");
        }

        LOG_TRACE("Created Vulkan framebuffer");
    }

    VulkanFramebuffer::~VulkanFramebuffer() {
        vkDestroyFramebuffer(device_owner.get_vk_device(), backend, nullptr);

        LOG_TRACE("Destroyed Vulkan framebuffer");
    }
}
