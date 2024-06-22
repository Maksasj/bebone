#include "vulkan_texture.h"

#include "vulkan_device.h"
#include "vulkan_command_buffer_pool.h"

namespace bebone::gfx::vulkan {
    using namespace bebone::core;
    using namespace bebone::assets;

    VulkanTexture::VulkanTexture(
        VulkanDevice& device,
        std::shared_ptr<VulkanCommandBufferPool>& commandBufferPool,
        const std::shared_ptr<Image<ColorRGBA>>& raw
    ) {
        // Todo make create_image_memory function to device
        image = device.create_image(
            VK_FORMAT_R32G32B32A32_SFLOAT,
            { static_cast<uint32_t>(raw->get_width()), static_cast<uint32_t>(raw->get_height()), 1},
            { .usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT }
        );

        auto memReq = image->get_memory_requirements(device);

        memory = device.create_device_memory(memReq, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        memory->bind_image_memory(device, image);

        image->transition_layout(*commandBufferPool, device, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

        auto size = raw->get_width() * raw->get_height() * sizeof(ColorRGBA);
        auto staging = device.create_buffer_memory(size);
        staging.memory->upload_data(device, raw->data(), size);

        commandBufferPool->copy_buffer_to_image(device, staging.buffer, image, raw->get_width(), raw->get_height(), 1);

        staging.memory->destroy(device); // Todo
        staging.buffer->destroy(device); // Todo

        image->transition_layout(*commandBufferPool, device, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

        sampler = device.create_sampler();
        view = device.create_image_view(*image, VK_FORMAT_R32G32B32A32_SFLOAT);
    }

    void VulkanTexture::destroy(VulkanDevice &device) {
        sampler->destroy(device);
        view->destroy(device);
        memory->destroy(device);
        image->destroy(device);
    }
}
