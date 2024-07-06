#include "vulkan_render_target.h"

#include "vulkan_image.h"
#include "vulkan_image_view.h"
#include "vulkan_device_memory.h"
#include "vulkan_swap_chain.h"

namespace bebone::gfx {
    VulkanRenderTarget::VulkanRenderTarget(
        VulkanDevice& device,
        std::vector<VulkanSwapChainImageTuple>& image_views,
        std::shared_ptr<VulkanRenderPass> render_pass,
        VkExtent2D extent // Todo, extent should be handled in another place
    ) : color_attachments(image_views) {
        // Create depth resources
        auto depthFormat = device.find_depth_format();
        depth_attachments.reserve(image_views.size());

        for(size_t i = 0; i < image_views.size(); ++i) {
            auto image = device.create_image(depthFormat, { extent.width, extent.height, 1}, {
                .usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
            });

            auto requirements = image->get_memory_requirements(device);

            auto memory = device.create_device_memory(requirements, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
            memory->bind_image_memory(device, *image);

            auto view = device.create_image_view(*image, depthFormat, {
                .subresource_range = { .aspect_mask = VK_IMAGE_ASPECT_DEPTH_BIT },
            });

            depth_attachments.emplace_back(image, view, memory);
        }

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
