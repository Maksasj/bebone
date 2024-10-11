#ifndef _BEBONE_GFX_VULKAN_SHADER_MODULE_H_
#define _BEBONE_GFX_VULKAN_SHADER_MODULE_H_

#include "../gfx_backend.h"

#include "../shaders/shader_code.h"
#include "../shaders/shader_compiler.h"
#include "../shaders/shader_source.h"
#include "../shaders/shader_type.h"
#include "../shaders/spirv_shader_compiler.h"

#include "interface/i_vulkan_device.h"

namespace bebone::gfx {
    class VulkanShaderModule : private core::NonCopyable {
        public:
            VkShaderModule shader_module;

        private:
            IVulkanDevice& device_owner;

        public:
            ShaderType type;

            VulkanShaderModule(IVulkanDevice& device, const ShaderCode& code);
            VulkanShaderModule(IVulkanDevice& device, const std::string& source_code, const ShaderType& type);

            ~VulkanShaderModule();
    };
}

#endif