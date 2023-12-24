#include "render_target.h"

#include "vulkan/vulkan_image.h"
#include "vulkan/vulkan_image_view.h"

namespace bebone::gfx {
    RenderTarget::RenderTarget(
        VulkanDevice& device,
        std::vector<std::shared_ptr<VulkanImage>>& swapChainImages,
        VkFormat _imageFormat,
        VkExtent2D _extent
    ) : renderPass(device, _imageFormat), swapChainImages(swapChainImages), imageFormat(_imageFormat), extent(_extent) {

        for(auto& image : swapChainImages)
            image->create_image_view(device, imageFormat);

        create_depth_resources(device);
        create_framebuffers(device);
    }

    void RenderTarget::create_framebuffers(VulkanDevice& device) {
        swapChainFramebuffers.resize(swapChainImages.size());

        for (size_t i = 0; i < swapChainImages.size(); i++) {
            // std::array<VkImageView, 2> attachments = { swapChainImages[i]->imageView->backend, depthImageViews[i]};
            // std::array<VkImageView, 2> attachments = { swapChainImageViews[i], depthImageViews[i]};
            std::array<VkImageView, 2> attachments = { swapChainImages[i]->imageView->backend, depthImageViews[i]};

            VkFramebufferCreateInfo framebufferInfo = {};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = renderPass.backend;
            framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
            framebufferInfo.pAttachments = attachments.data();
            framebufferInfo.width = extent.width;
            framebufferInfo.height = extent.height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(device.device(), &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create framebuffer!");
            }
        }
    }

    void RenderTarget::create_depth_resources(VulkanDevice& device) {
        VkFormat depthFormat = device.find_depth_format();

        depthImages.resize(swapChainImages.size());
        depthImageMemorys.resize(swapChainImages.size());
        depthImageViews.resize(swapChainImages.size());

        for(size_t i = 0; i < depthImages.size(); ++i) {
            VkImageCreateInfo imageInfo{};
            imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
            imageInfo.imageType = VK_IMAGE_TYPE_2D;
            imageInfo.extent.width = extent.width;
            imageInfo.extent.height = extent.height;
            imageInfo.extent.depth = 1;
            imageInfo.mipLevels = 1;
            imageInfo.arrayLayers = 1;
            imageInfo.format = depthFormat;
            imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
            imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
            imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
            imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
            imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
            imageInfo.flags = 0;

            device.create_image_with_info(imageInfo, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, depthImages[i], depthImageMemorys[i]);

            VkImageViewCreateInfo viewInfo{};
            viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            viewInfo.image = depthImages[i];
            viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
            viewInfo.format = depthFormat;
            viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
            viewInfo.subresourceRange.baseMipLevel = 0;
            viewInfo.subresourceRange.levelCount = 1;
            viewInfo.subresourceRange.baseArrayLayer = 0;
            viewInfo.subresourceRange.layerCount = 1;

            if (vkCreateImageView(device.device(), &viewInfo, nullptr, &depthImageViews[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create texture image view!");
            }
        }
    }

    void RenderTarget::destroy(VulkanDevice& device) {
        // Todo move this some where else
        renderPass.destroy(device);

        // Todo move this some where else
        for (auto imageView : swapChainImages)
            imageView->imageView->destroy(device);

        for (size_t i = 0; i < depthImages.size(); i++) {
            vkDestroyImageView(device.device(), depthImageViews[i], nullptr);
            vkDestroyImage(device.device(), depthImages[i], nullptr);
            vkFreeMemory(device.device(), depthImageMemorys[i], nullptr);
        }

        for (auto framebuffer : swapChainFramebuffers) {
            vkDestroyFramebuffer(device.device(), framebuffer, nullptr);
        }
    }
}
