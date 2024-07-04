#include "vulkan_render_pass.h"

namespace bebone::gfx {
    VulkanRenderPass::VulkanRenderPass(VulkanDevice& device, const std::vector<VulkanAttachment>& attachments) {
        auto descriptions = std::vector<VkAttachmentDescription> {};
        descriptions.reserve(attachments.size());

        for(const auto& attachment : attachments)
            descriptions.push_back(attachment.description);

        auto color_attachments_ref = std::vector<VkAttachmentReference> {};
        auto depth_attachment_ref = VkAttachmentReference {}; // Only one depth attachment

        for(size_t i = 0; i < attachments.size(); ++i) {
            const auto& attachment = attachments[i];

            // Todo, only one depth attachment is allowed
            if(attachment.type == Depth) {
                depth_attachment_ref.attachment = i;
                depth_attachment_ref.layout = attachment.layout;
            } else if(attachment.type == Color)
                color_attachments_ref.push_back(VkAttachmentReference{ static_cast<uint32_t>(i), attachment.layout });
        }

        // Main subpass
        auto subpass = VkSubpassDescription {};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS; // Todo
        subpass.colorAttachmentCount = color_attachments_ref.size();
        subpass.pColorAttachments = color_attachments_ref.data();
        subpass.pDepthStencilAttachment = &depth_attachment_ref;

        // and it dependencies
        VkSubpassDependency dependency = {};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.srcAccessMask = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
        dependency.dstSubpass = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

        VkRenderPassCreateInfo render_pass_info = {};
        render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        render_pass_info.attachmentCount = static_cast<uint32_t>(descriptions.size());
        render_pass_info.pAttachments = descriptions.data();

        render_pass_info.subpassCount = 1;
        render_pass_info.pSubpasses = &subpass;

        render_pass_info.dependencyCount = 1;
        render_pass_info.pDependencies = &dependency;

        if(vkCreateRenderPass(device.device, &render_pass_info, nullptr, &backend) != VK_SUCCESS)
            throw std::runtime_error("failed to create render pass!");
    }

    void VulkanRenderPass::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;

        vkDestroyRenderPass(device.device, backend, nullptr);

        mark_destroyed();
    }
}
