#include "vulkan_texture_tuple.h"

#include "vulkan_device.h"
#include "vulkan_command_buffer_pool.h"
#include "vulkan_buffer_memory.h"

namespace bebone::gfx {
    using namespace bebone::core;
    using namespace bebone::assets;

    VulkanTexture::VulkanTexture(
        VulkanDevice& device,
        const std::shared_ptr<Image<ColorRGBA>>& raw
    ) {
        image = device.create_image(ColorRGBA::get_vulkan_format(), { static_cast<uint32_t>(raw->get_width()), static_cast<uint32_t>(raw->get_height()), 1}, { .usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT });

        auto req = image->get_memory_requirements();

        memory = device.create_device_memory(req, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
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

        sampler = device.create_sampler();
        view = device.create_image_view(*image, ColorRGBA::get_vulkan_format());
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
        image = device.create_image(ColorRGBA::get_vulkan_format(), extent, { .usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT });

        auto req = image->get_memory_requirements();

        memory = device.create_device_memory(req, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        memory->bind_image_memory(image);

        sampler = device.create_sampler();
        view = device.create_image_view(*image, image_format);
    }

    VkMemoryRequirements VulkanTexture::get_memory_requirements() const {
        return image->get_memory_requirements();
    }

    VkImage VulkanTexture::get_vulkan_image() const {
        return image->get_vulkan_image();
    }

    VkExtent3D VulkanTexture::get_extent() const {
        return image->get_extent();
    }

    VkImageView VulkanTexture::get_vulkan_image_view() const {
        return view->get_vulkan_image_view();
    }

    VkSampler VulkanTexture::get_vulkan_image_sampler() const {
        return sampler->get_vulkan_image_sampler();
    }
}
