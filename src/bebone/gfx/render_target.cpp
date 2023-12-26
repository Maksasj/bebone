#include "render_target.h"

#include "vulkan/vulkan_image.h"
#include "vulkan/vulkan_image_view.h"
#include "vulkan/vulkan_device_memory.h"
#include "vulkan/vulkan_swap_chain.h"

namespace bebone::gfx {
    RenderTarget::RenderTarget(
        VulkanDevice& device,
        std::vector<VulkanSwapChainImageTuple>& swapChainImages,
        VkFormat imageFormat,
        VkExtent2D extent
    ) : swapChainImages(swapChainImages) {

        // Create render pass
        renderPass = std::make_shared<VulkanRenderPass>(device, imageFormat);

        // Create depth resources
        auto depthFormat = device.find_depth_format();

        for(size_t i = 0; i < swapChainImages.size(); ++i) {
            auto image = device.create_image({
                .format = depthFormat,
                .extent = { extent.width, extent.height, 1},
                .usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
            });

            auto memRequirements = image->get_memory_requirements(device);

            auto memory = device.create_device_memory(memRequirements, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
            memory->bind_image_memory(device, *image);

            auto view = device.create_image_view(*image, depthFormat, {
                .subresourceRange = { .aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT },
            });

            depthImages.push_back({image, view, memory});
        }

        // Create frame buffers
        for(size_t i = 0; i < swapChainImages.size(); ++i) {
            auto attachments = std::vector { swapChainImages[i].view, depthImages[i].view };
            auto framebuffer = std::make_shared<VulkanFramebuffer>(device, attachments, renderPass, extent);

            swapChainFramebuffers.push_back(framebuffer);
        }
    }

    void RenderTarget::destroy(VulkanDevice& device) {
        renderPass->destroy(device);

        for(auto& image : swapChainImages)
            image.view->destroy(device); // Since image is provided by swap chain we should not destroy it, only view

        for(auto& image : depthImages) {
            image.memory->destroy(device);
            image.view->destroy(device);
            image.image->destroy(device);
        }

        for (auto& framebuffer : swapChainFramebuffers)
            framebuffer->destroy(device);
    }
}
