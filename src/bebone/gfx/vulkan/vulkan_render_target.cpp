#include "vulkan_render_target.h"

#include "vulkan_image.h"
#include "vulkan_image_view.h"
#include "vulkan_device_memory.h"
#include "vulkan_swap_chain.h"

namespace bebone::gfx {
    VulkanRenderTarget::VulkanRenderTarget(
        VulkanDevice& device,
        std::shared_ptr<VulkanRenderPass>& render_pass,
        std::vector<VulkanSwapChainImageTuple>& image_views,
        VkExtent2D extent // Todo, extent should be handled in another place
    ) : color_attachments(image_views) {
        depth_attachments = device.create_depth_image_tuples( {extent.width, extent.height, 1}, image_views.size());

        // Create frame buffers
        for(size_t i = 0; i < image_views.size(); ++i) {
            auto attachments = std::vector { image_views[i].view, depth_attachments[i].view };
            auto framebuffer = device.create_framebuffer(attachments, render_pass, extent);

            framebuffers.push_back(framebuffer);
        }
    }

    void VulkanRenderTarget::destroy(VulkanDevice& device) {
        // Todo
        for(auto& texture : color_attachments)
            texture.destroy(device); // Since image is provided by swap chain we should not destroy it, only view

        for(auto& tuple : depth_attachments)
            tuple.destroy(device);

        for (auto& framebuffer : framebuffers)
            framebuffer->destroy(device);

        mark_destroyed();
    }
}
