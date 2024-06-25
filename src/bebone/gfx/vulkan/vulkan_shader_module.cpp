#include "vulkan_shader_module.h"

#include "vulkan_device.h"

namespace bebone::gfx::vulkan {
    VulkanShaderModule::VulkanShaderModule(VulkanDevice& device, const ShaderCode& shaderCode) : shaderType(shaderCode.get_shader_type()) {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = shaderCode.get_byte_code().size() * sizeof(unsigned int);
        createInfo.pCode = reinterpret_cast<const uint32_t*>(shaderCode.get_byte_code().data());

        if(vkCreateShaderModule(device.device(), &createInfo, nullptr, &backend) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create shader module");
        }
    }

    void VulkanShaderModule::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;

        vkDestroyShaderModule(device.device(), backend, nullptr);

        mark_destroyed();
    }
}
