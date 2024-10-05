#ifndef _BEBONE_GFX_VULKAN_SHADER_MODULE_H_
#define _BEBONE_GFX_VULKAN_SHADER_MODULE_H_

#include "../gfx_backend.h"

#include "vulkan_wrapper.tpp"

#include "../shaders/shader_code.h"
#include "../shaders/shader_compiler.h"
#include "../shaders/shader_source.h"
#include "../shaders/shader_type.h"
#include "../shaders/spirv_shader_compiler.h"

namespace bebone::gfx {
    class VulkanDevice;

    class VulkanShaderModule : public VulkanWrapper<VkShaderModule>, private core::NonCopyable {
        private:
            VulkanDevice& device;

        public:
            ShaderType type;

            VulkanShaderModule(VulkanDevice& device, const ShaderCode& code);
            ~VulkanShaderModule();

            // void destroy(VulkanDevice& device) override;
    };
}

#endif