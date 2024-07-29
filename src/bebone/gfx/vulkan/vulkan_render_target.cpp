#include "vulkan_render_target.h"

#include "vulkan_image.h"
#include "vulkan_image_view.h"
#include "vulkan_device_memory.h"
#include "vulkan_swap_chain.h"

namespace bebone::gfx {
    VulkanRenderTarget::VulkanRenderTarget(
        VulkanDevice& device,
        std::shared_ptr<VulkanRenderPass>& render_pass
    ) {
        // Create color attachments
        color_attachments.reserve(render_pass->get_color_attachments_count());

        for(auto& attachment : render_pass->get_attachments()) {
            if(attachment.type != Color)
                continue;

            auto frame_attachments = std::vector<std::shared_ptr<IVulkanAttachment>> {};
            frame_attachments.reserve(3); // Todo, 3 should be configurable

            for(size_t f = 0; f < 3; ++f) // Todo, 3 should be configurable
                frame_attachments.push_back(device.create_texture(attachment.extent, attachment.description.format));

            color_attachments.push_back(frame_attachments);
        }

        // Create depth attachments
        if(render_pass->get_depth_attachment().has_value()) {
            auto attachment = render_pass->get_depth_attachment().value();

            auto frame_attachments = std::vector<std::shared_ptr<IVulkanAttachment>> {};
            frame_attachments.reserve(3); // Todo, 3 should be configurable

            for(size_t f = 0; f < 3; ++f) // Todo, 3 should be configurable
                frame_attachments.push_back(device.create_depth_image_tuple(attachment.extent));

            depth_attachments = frame_attachments;
        }

        // Create frame buffers
        for(size_t i = 0; i < 3; ++i) { // Todo, 3 should be configurable
            auto attachments = std::vector<std::shared_ptr<VulkanImageView>> {};
            attachments.reserve(color_attachments.size());

            for(size_t a = 0; a < color_attachments.size(); ++a) {
                auto attachment = color_attachments[a][i];
                attachments.push_back(attachment->get_view().value());
            }

            // Todo, depth attachment order should be configurable
            if(!depth_attachments.empty())
                attachments.push_back(depth_attachments[i]->get_view().value());

            auto framebuffer = device.create_framebuffer(attachments, render_pass, render_pass->get_extent());
            framebuffers.push_back(framebuffer);
        }
    }

    VulkanRenderTarget::VulkanRenderTarget(
        VulkanDevice& device,
        std::shared_ptr<VulkanRenderPass>& render_pass,
        std::vector<std::shared_ptr<VulkanSwapChainImageTuple>>& images
    ) {
        // We do need to create color attachments, since swap chain handles them

        // Create depth attachments
        if(render_pass->get_depth_attachment().has_value()) {
            auto attachment = render_pass->get_depth_attachment().value();

            auto frame_attachments = std::vector<std::shared_ptr<IVulkanAttachment>> {};
            frame_attachments.reserve(3); // Todo, 3 should be configurable

            for(size_t f = 0; f < 3; ++f) // Todo, 3 should be configurable
                frame_attachments.push_back(device.create_depth_image_tuple(attachment.extent));

            depth_attachments = frame_attachments;
        }

        // Create frame buffers
        for(size_t i = 0; i < 3; ++i) { // Todo, 3 should be configurable
            // auto attachments = std::vector { image_views[i]->get_view().value(), depth_attachments[i]->get_view().value() };

            auto attachments = std::vector<std::shared_ptr<VulkanImageView>> {};
            attachments.push_back(images[i]->view);

            if(!depth_attachments.empty())
                attachments.push_back(depth_attachments[i]->get_view().value());

            auto framebuffer = device.create_framebuffer(attachments, render_pass, render_pass->get_extent());

            framebuffers.push_back(framebuffer);
        }
    }

    vector<shared_ptr<IVulkanAttachment>>& VulkanRenderTarget::get_color_attachment(const size_t& index) {
        return color_attachments[index];
    }

    vector<shared_ptr<IVulkanAttachment>>& VulkanRenderTarget::depth_attachment() {
        return depth_attachments;
    }

    /*
    void VulkanRenderTarget::destroy(VulkanDevice& device) {
        // Todo
        for(auto& frame : color_attachments)
            for(auto& tuple : frame)
                tuple->destroy(device); // Since image is provided by swap chain we should not destroy it, only view

        for(auto& tuple : depth_attachments)
            tuple->destroy(device);

        for (auto& framebuffer : framebuffers)
            framebuffer->destroy(device);

        mark_destroyed();
    }
    */
}
