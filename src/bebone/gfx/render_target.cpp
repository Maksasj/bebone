#include "render_target.h"

#include "vulkan/vulkan_image.h"
#include "vulkan/vulkan_image_view.h"
#include "vulkan/vulkan_device_memory.h"
#include "vulkan/vulkan_swap_chain.h"

namespace bebone::gfx {
    RenderTarget::RenderTarget(
        VulkanDevice& device,
        std::vector<VulkanSwapChainImage>& swapChainImages,
        VkFormat imageFormat,
        VkExtent2D extent
    ) : swapChainImages(swapChainImages) {

        // Create render pass
        renderPass = std::make_shared<VulkanRenderPass>(device, imageFormat);

        // Create depth resources
        VkFormat depthFormat = device.find_depth_format();
        for(size_t i = 0; i < swapChainImages.size(); ++i) {
            VulkanDepthImage depthImage;

            depthImage.image = VulkanImage::create_default_depth_image(device, extent, depthFormat);

            VkMemoryRequirements memRequirements; // Todo maybe we can move this thing into image && buffer
            vkGetImageMemoryRequirements(device.device(), depthImage.image->backend, &memRequirements);
            depthImage.memory = std::make_shared<VulkanDeviceMemory>(device, memRequirements, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
            depthImage.memory->bind_image_memory(device, *depthImage.image);

            depthImage.view = VulkanImageView::create_default_depth_image_view(device, depthImage.image, depthFormat);

            depthImages.push_back(depthImage);
        }

        // Create frame buffers
        for(size_t i = 0; i < swapChainImages.size(); ++i) {
            auto attachments = std::vector{ swapChainImages[i].view, depthImages[i].view };
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
