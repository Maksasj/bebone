#include "vulkan_shader_module.h"

#include "vulkan_device.h"

namespace bebone::gfx {
    VulkanShaderModule::VulkanShaderModule(IVulkanDevice& device, const ShaderCode& code) : device_owner(device), type(code.get_shader_type()) {
        VkShaderModuleCreateInfo create_info{};

        create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        create_info.codeSize = code.get_byte_code().size() * sizeof(unsigned int);
        create_info.pCode = reinterpret_cast<const uint32_t*>(code.get_byte_code().data());

        if(vkCreateShaderModule(device_owner.get_vk_device(), &create_info, nullptr, &shader_module) != VK_SUCCESS) {
            LOG_ERROR("Failed to create shader module");
            throw std::runtime_error("Failed to create shader module");
        }

        LOG_TRACE("Created Vulkan shader module");
    }

    VulkanShaderModule::VulkanShaderModule(IVulkanDevice& device, const std::string& source_code, const ShaderType& type) : device_owner(device), type(type) {
        auto shader_compiler = SpirVShaderCompiler();

        shader_compiler.add_shader_source(ShaderSource(
                source_code,
                type
        ));

        auto shader_code = shader_compiler.compile(type);

        VkShaderModuleCreateInfo create_info{};

        create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        create_info.codeSize = shader_code.get_byte_code().size() * sizeof(unsigned int);
        create_info.pCode = reinterpret_cast<const uint32_t*>(shader_code.get_byte_code().data());

        if(vkCreateShaderModule(device_owner.get_vk_device(), &create_info, nullptr, &shader_module) != VK_SUCCESS) {
            LOG_ERROR("Failed to create shader module");
            throw std::runtime_error("Failed to create shader module");
        }

        LOG_TRACE("Created Vulkan shader module");
    }

    VulkanShaderModule::~VulkanShaderModule() {
        vkDestroyShaderModule(device_owner.get_vk_device(), shader_module, nullptr);

        LOG_TRACE("Destroyed Vulkan shader module");
    }
}
