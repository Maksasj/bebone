#include "vulkan_texture_tuple.h"

#include "vulkan_device.h"
#include "vulkan_command_buffer_pool.h"
#include "vulkan_buffer_memory.h"

#include "vulkan_image.h"

namespace bebone::gfx {
    using namespace bebone::core;
    using namespace bebone::assets;

    VulkanTexture::VulkanTexture(
        VulkanDevice& device,
        const std::shared_ptr<Image<ColorRGBA>>& raw
    ) {
        VkExtent3D extent = { static_cast<uint32_t>(raw->get_width()), static_cast<uint32_t>(raw->get_height()), 1};

        VulkanImageInfo image_info{};
        image_info.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
        image = std::make_unique<VulkanImage>(device, ColorRGBA::get_vulkan_format(), extent, image_info);

        auto req = image->get_memory_requirements();

        memory = std::make_unique<VulkanDeviceMemory>(device, req, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        memory->bind_image_memory(image);

        image->transition_layout(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

        auto size = raw->get_width() * raw->get_height() * sizeof(ColorRGBA);
        auto staged = VulkanBufferMemory(device, size);

        staged.upload_data(raw->data(), size);

        // Todo Probably uploading data to gpu need some sort of render graph api
        staged.copy_to_image(*image);

        /*
        device.destroy_all(staged);
        device.collect_garbage();
        */

        image->transition_layout(VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

        sampler = std::make_unique<VulkanSampler>(device);
        view = std::make_unique<VulkanImageView>(device, *image, ColorRGBA::get_vulkan_format());
    }

    VulkanTexture::VulkanTexture(
        std::unique_ptr<VulkanImage>& image,
        std::unique_ptr<VulkanDeviceMemory>& memory,
        std::unique_ptr<VulkanImageView>& view,
        std::unique_ptr<VulkanSampler>& sampler
    ) : image(std::move(image)), memory(std::move(memory)), view(std::move(view)), sampler(std::move(sampler)) {

    }

    VulkanTexture::VulkanTexture(
        VulkanDevice& device,
        VkExtent3D extent,
        VkFormat image_format
    ) {
        VulkanImageInfo image_info{};
        image_info.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
        image = std::make_unique<VulkanImage>(device, ColorRGBA::get_vulkan_format(), extent, image_info);

        auto req = image->get_memory_requirements();

        memory = std::make_unique<VulkanDeviceMemory>(device, req, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        memory->bind_image_memory(image);

        sampler = std::make_unique<VulkanSampler>(device);

        view = std::make_unique<VulkanImageView>(device, *image, image_format);
    }

    VkMemoryRequirements VulkanTexture::get_memory_requirements() const {
        return image->get_memory_requirements();
    }

    VkImage VulkanTexture::get_vk_image() const {
        return image->get_vk_image();
    }

    VkExtent3D VulkanTexture::get_extent() const {
        return image->get_extent();
    }

    VkImageView VulkanTexture::get_vk_image_view() const {
        return view->get_vk_image_view();
    }

    VkSampler VulkanTexture::get_vk_image_sampler() const {
        return sampler->get_vk_image_sampler();
    }
}
