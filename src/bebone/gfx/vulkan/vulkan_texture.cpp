#include "vulkan_texture.h"

#include "vulkan_device.h"
#include "vulkan_command_buffer_pool.h"

namespace bebone::gfx::vulkan {
    using namespace bebone::core;
    using namespace bebone::assets;

    VulkanTexture::VulkanTexture(
        VulkanDevice& device,
        std::shared_ptr<VulkanCommandBufferPool>& command_buffer_pool,
        const std::shared_ptr<Image<ColorRGBA>>& raw
    ) {
        auto [im, mem] = device.create_image_memory(VK_FORMAT_R32G32B32A32_SFLOAT,
            { static_cast<uint32_t>(raw->get_width()), static_cast<uint32_t>(raw->get_height()), 1},
            { .usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT }
        );

        image = im; memory = mem;

        image->transition_layout(*command_buffer_pool, device, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

        auto size = raw->get_width() * raw->get_height() * sizeof(ColorRGBA);
        auto staged = device.create_buffer_memory(size);
        staged.upload_data(device, raw->data(), size);

        // Todo Probably uploading data to gpu need some sort of render graph api
        command_buffer_pool->copy_buffer_to_image(device, staged.buffer, image, raw->get_width(), raw->get_height(), 1);

        staged.destroy(device);

        image->transition_layout(*command_buffer_pool, device, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

        sampler = device.create_sampler();
        view = device.create_image_view(*image, VK_FORMAT_R32G32B32A32_SFLOAT);
    }

    void VulkanTexture::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;

        sampler->destroy(device);
        view->destroy(device);
        memory->destroy(device);
        image->destroy(device);

        mark_destroyed();
    }
}
