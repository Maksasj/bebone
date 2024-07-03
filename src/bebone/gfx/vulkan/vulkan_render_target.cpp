#include "vulkan_render_target.h"

#include "vulkan_image.h"
#include "vulkan_image_view.h"
#include "vulkan_device_memory.h"
#include "vulkan_swap_chain.h"

namespace bebone::gfx {
    VulkanRenderTarget::VulkanRenderTarget(
        VulkanDevice& device,
        std::vector<VulkanSwapChainImageTuple>& swap_chain_images,
        VkFormat image_format,
        VkExtent2D extent
    ) : swap_chain_images(swap_chain_images) {
        // Todo, this should be moved outside
        render_pass = device.create_render_pass(image_format);

        // Create depth resources
        auto depthFormat = device.find_depth_format();
        depth_images.reserve(swap_chain_images.size());

        for(size_t i = 0; i < swap_chain_images.size(); ++i) {
            auto image = device.create_image(depthFormat, { extent.width, extent.height, 1}, {
                .usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
            });

            auto requirements = image->get_memory_requirements(device);

            auto memory = device.create_device_memory(requirements, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
            memory->bind_image_memory(device, *image);

            auto view = device.create_image_view(*image, depthFormat, {
                .subresource_range = { .aspect_mask = VK_IMAGE_ASPECT_DEPTH_BIT },
            });

            depth_images.emplace_back(image, view, memory);
        }

        // Create frame buffers
        for(size_t i = 0; i < swap_chain_images.size(); ++i) {
            auto attachments = std::vector { swap_chain_images[i].view, depth_images[i].view };
            auto framebuffer = device.create_framebuffer(attachments, render_pass, extent);

            framebuffers.push_back(framebuffer);
        }
    }

    void VulkanRenderTarget::destroy(VulkanDevice& device) {
        render_pass->destroy(device);

        for(auto& [_, view] : swap_chain_images)
            view->destroy(device); // Since image is provided by swap chain we should not destroy it, only view

        for(auto& [memory, view, image] : depth_images) { // Todo
            memory->destroy(device);
            view->destroy(device);
            image->destroy(device);
        }

        for (auto& framebuffer : framebuffers)
            framebuffer->destroy(device);

        mark_destroyed();
    }
}
