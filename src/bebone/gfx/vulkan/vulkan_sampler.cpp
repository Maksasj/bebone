#include "vulkan_sampler.h"

#include "vulkan_device.h"

namespace bebone::gfx {
    using namespace bebone::core;

    VulkanSampler::VulkanSampler(VulkanDevice& device) {
        VkSamplerCreateInfo sampler_info{};

        sampler_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        sampler_info.magFilter = VK_FILTER_LINEAR;
        sampler_info.minFilter = VK_FILTER_LINEAR;
        sampler_info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
        sampler_info.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        sampler_info.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        sampler_info.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        sampler_info.mipLodBias = 0.0f;
        sampler_info.compareOp = VK_COMPARE_OP_NEVER;
        sampler_info.minLod = 0.0f;
        sampler_info.maxLod = 0.0f;
        sampler_info.maxAnisotropy = 1.0f;
        sampler_info.anisotropyEnable = VK_FALSE;
        sampler_info.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;

        // Todo
        vkCreateSampler(device.device, &sampler_info, nullptr, &backend);
    }

    void VulkanSampler::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;

        vkDestroySampler(device.device, backend, nullptr);

        mark_destroyed();
    }
}
