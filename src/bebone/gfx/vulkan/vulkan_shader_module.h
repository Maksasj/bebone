#ifndef VULKAN_SHADER_MODULE_H
#define VULKAN_SHADER_MODULE_H

#include "../gfx_backend.h"

#include "../shaders/shader_code.h"
#include "vulkan_wrapper.tpp"

namespace bebone::gfx {
    class VulkanDevice;

    class VulkanShaderModule : public VulkanWrapper<VkShaderModule>, private core::NonCopyable {
        public:
            VulkanShaderModule(VulkanDevice& device, const ShaderCode& shaderCode);

            void destroy(VulkanDevice& device) override;
    };
}

#endif