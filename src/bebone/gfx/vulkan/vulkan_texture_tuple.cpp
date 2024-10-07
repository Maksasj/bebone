#include "vulkan_texture_tuple.h"

#include "vulkan_device.h"
#include "vulkan_command_buffer_pool.h"

namespace bebone::gfx {
    using namespace bebone::core;
    using namespace bebone::assets;

    VulkanTexture::VulkanTexture(
        VulkanDevice& device,
        const std::shared_ptr<Image<ColorRGBA>>& raw
    ) {
        auto tuple = device.create_image_memory(ColorRGBA::get_vulkan_format(),
            { static_cast<uint32_t>(raw->get_width()), static_cast<uint32_t>(raw->get_height()), 1},
            { .usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT }
        );

        image = std::move(tuple->image),
        memory = std::move(tuple->memory);

        image->transition_layout(VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

        auto size = raw->get_width() * raw->get_height() * sizeof(ColorRGBA);
        auto staged = device.create_buffer_memory(size);
        staged->upload_data(raw->data(), size);

        // Todo Probably uploading data to gpu need some sort of render graph api
        staged->buffer->copy_to_image(image);

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
        auto tuple = device.create_image_memory(image_format, extent, // Todo, image_format should be configurable
            { .usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT }
        );  // Todo, usage should be configurable

        image = std::move(tuple->image),
        memory = std::move(tuple->memory);

        sampler = device.create_sampler();
        view = device.create_image_view(*image, image_format);
    }

    VkImage VulkanTexture::get_vulkan_image() const {
        return image->backend;
    }

    VkImageView VulkanTexture::get_vulkan_image_view() const {
        return view->backend;
    }

    VkSampler VulkanTexture::get_vulkan_image_sampler() const {
        return sampler->backend;
    }

    /*
    void VulkanTexture::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;

        sampler->destroy(device);
        view->destroy(device);
        memory->destroy(device);
        image->destroy(device);

        mark_destroyed();
    }
    */
}
