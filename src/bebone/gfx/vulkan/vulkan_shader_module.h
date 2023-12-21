#ifndef VULKAN_SHADER_MODULE_H
#define VULKAN_SHADER_MODULE_H

#include "../gfx_backend.h"

#include "../shaders/shader_code.h"

namespace bebone::gfx {
    class VulkanDevice;

    class VulkanShaderModule : private core::NonCopyable {
        public:
            VkShaderModule shader;

            VulkanShaderModule(VulkanDevice& device, const ShaderCode& shaderCode);
    };
}

#endif