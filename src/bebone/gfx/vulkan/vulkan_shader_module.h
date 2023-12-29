#ifndef _BEBONE_GFX_VULKAN_VULKAN_SHADER_MODULE_H_
#define _BEBONE_GFX_VULKAN_VULKAN_SHADER_MODULE_H_

#include "../gfx_backend.h"

#include "../shaders/shader_code.h"
#include "vulkan_wrapper.tpp"

namespace bebone::gfx {
    class VulkanDevice;

    class VulkanShaderModule : public VulkanWrapper<VkShaderModule>, private core::NonCopyable {
        public:
            ShaderType shaderType;

            VulkanShaderModule(VulkanDevice& device, const ShaderCode& shaderCode);

            void destroy(VulkanDevice& device) override;
    };
}

#endif