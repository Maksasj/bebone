#include "vulkan_framebuffer.h"

#include "vulkan_device.h"
#include "vulkan_image_view.h"
#include "vulkan_render_pass.h"

namespace bebone::gfx {
    using namespace bebone::core;

    VulkanFramebuffer::VulkanFramebuffer(
        VulkanDevice& device,
        const std::vector<std::shared_ptr<VulkanImageView>>& attachment_views,
        const std::shared_ptr<VulkanRenderPass>& render_pass,
        VkExtent2D extent
    ) : device(device) {
        auto attachments = std::vector<VkImageView> {};
        attachments.reserve(attachment_views.size());
        
        for(auto& view : attachment_views)
            attachments.push_back(view->backend);

        VkFramebufferCreateInfo create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        create_info.renderPass = render_pass->backend;
        create_info.attachmentCount = static_cast<uint32_t>(attachments.size());
        create_info.pAttachments = attachments.data();
        create_info.width = extent.width;
        create_info.height = extent.height;
        create_info.layers = 1;

        if(vkCreateFramebuffer(device.device, &create_info, nullptr, &backend) != VK_SUCCESS) {
            LOG_ERROR("Failed to create framebuffer");
            throw std::runtime_error("failed to create framebuffer!");
        }

        LOG_TRACE("Created Vulkan framebuffer");
    }

    VulkanFramebuffer::~VulkanFramebuffer() {
        vkDestroyFramebuffer(device.device, backend, nullptr);

        LOG_TRACE("Destroyed Vulkan framebuffer");
    }

    /*
    void VulkanFramebuffer::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;
            
        vkDestroyFramebuffer(device.device, backend, nullptr);

        LOG_TRACE("Destroyed Vulkan framebuffer");

        mark_destroyed();
    }
    */
}
