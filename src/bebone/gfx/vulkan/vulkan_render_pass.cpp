#include "vulkan_render_pass.h"

namespace bebone::gfx {
    VulkanRenderPass::VulkanRenderPass(
        VulkanDevice& device,
        VkExtent2D extent,
        const std::vector<VulkanAttachmentDesc>& attachments
    ) : attachments(attachments), depth_attachment_index(0), has_depth_attachment_flag(false), color_attachment_count(0), extent(extent) {
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

                depth_attachment_index = i;
                has_depth_attachment_flag = true;
            } else if(attachment.type == Color)
                color_attachments_ref.push_back(VkAttachmentReference{ static_cast<uint32_t>(i), attachment.layout });
        }

        // We save color attachment count
        color_attachment_count = color_attachments_ref.size();

        // Main subpass
        auto subpass = VkSubpassDescription {};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS; // Todo
        subpass.colorAttachmentCount = color_attachments_ref.size();
        subpass.pColorAttachments = color_attachments_ref.data();

        if(has_depth_attachment_flag)
            subpass.pDepthStencilAttachment = &depth_attachment_ref;
        else
            subpass.pDepthStencilAttachment = nullptr;

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

        if(vkCreateRenderPass(device.device, &render_pass_info, nullptr, &backend) != VK_SUCCESS) {
            LOG_ERROR("Failed to create render pass");
            throw std::runtime_error("failed to create render pass!");
        }
    }

    std::optional<VulkanAttachmentDesc> VulkanRenderPass::get_depth_attachment() const {
        if(!has_depth_attachment_flag)
            return std::nullopt;

        return attachments[depth_attachment_index];
    }

    const size_t& VulkanRenderPass::get_color_attachments_count() const {
        return color_attachment_count;
    }

    const vector<VulkanAttachmentDesc>& VulkanRenderPass::get_attachments() const {
        return attachments;
    }

    const VkExtent2D& VulkanRenderPass::get_extent() const {
        return extent;
    }

    void VulkanRenderPass::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;

        vkDestroyRenderPass(device.device, backend, nullptr);

        mark_destroyed();
    }
}
