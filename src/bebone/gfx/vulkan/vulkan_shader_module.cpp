#include "vulkan_shader_module.h"

#include "vulkan_device.h"

namespace bebone::gfx {
    VulkanShaderModule::VulkanShaderModule(VulkanDevice& device, const ShaderCode& shaderCode) {
        VkShaderModuleCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = shaderCode.get_byte_code().size() * sizeof(unsigned int);
        createInfo.pCode = reinterpret_cast<const uint32_t*>(shaderCode.get_byte_code().data());

        if(vkCreateShaderModule(device.device(), &createInfo, nullptr, &shader) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create shader module");
        }
    }
}
