#include "vulkan_texture_tuple.h"

#include "vulkan_device.h"
#include "vulkan_command_pool.h"

namespace bebone::gfx {
    using namespace bebone::core;
    using namespace bebone::assets;

    VulkanTextureTuple::VulkanTextureTuple(
        VulkanDevice& device,
        const std::shared_ptr<Image<ColorRGBA>>& raw
    ) {
        auto [im, mem] = device.create_image_memory(ColorRGBA::get_vulkan_format(),
            { static_cast<uint32_t>(raw->get_width()), static_cast<uint32_t>(raw->get_height()), 1},
            { .usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT }
        );

        image = im; memory = mem;

        image->transition_layout(device, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

        auto size = raw->get_width() * raw->get_height() * sizeof(ColorRGBA);
        auto staged = device.create_buffer_memory(size);
        staged->upload_data(device, raw->data(), size);

        // Todo Probably uploading data to gpu need some sort of render graph api
        staged->buffer->copy_to_image(device, image);

        device.destroy_all(staged);
        device.collect_garbage();

        image->transition_layout(device, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

        sampler = device.create_sampler();
        view = device.create_image_view(*image, ColorRGBA::get_vulkan_format());
    }

    VulkanTextureTuple::VulkanTextureTuple(
        const std::shared_ptr<VulkanImage>& image,
        const std::shared_ptr<VulkanDeviceMemory>& memory,
        const std::shared_ptr<VulkanImageView>& view,
        const std::shared_ptr<VulkanSampler>& sampler
    ) : image(image), memory(memory), view(view), sampler(sampler) {

    }

    VulkanTextureTuple::VulkanTextureTuple(
        VulkanDevice& device,
        VkExtent3D extent,
        VkFormat image_format
    ) {
        auto [im, mem] = device.create_image_memory(image_format, extent, // Todo, image_format should be configurable
            { .usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT }
        );  // Todo, usage should be configurable

        image = im; memory = mem;

        sampler = device.create_sampler();
        view = device.create_image_view(*image, image_format);
    }

    std::optional<std::shared_ptr<VulkanImage>> VulkanTextureTuple::get_image() {
        return image;
    }

    std::optional<std::shared_ptr<VulkanImageView>> VulkanTextureTuple::get_view() {
        return view;
    }

    std::optional<std::shared_ptr<VulkanDeviceMemory>> VulkanTextureTuple::get_memory() {
        return memory;
    }

    std::optional<std::shared_ptr<VulkanSampler>> VulkanTextureTuple::get_sampler() {
        return sampler;
    }


    VulkanAttachmentType VulkanTextureTuple::get_type() const {
        return Color; // Todo, this may not be always true
    }

    /*
    void VulkanTextureTuple::destroy(VulkanDevice& device) {
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
