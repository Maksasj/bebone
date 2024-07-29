#include "vulkan_shader_module.h"

#include "vulkan_device.h"

namespace bebone::gfx {
    VulkanShaderModule::VulkanShaderModule(VulkanDevice& device, const ShaderCode& code) : type(code.get_shader_type()) {
        VkShaderModuleCreateInfo create_info{};

        create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        create_info.codeSize = code.get_byte_code().size() * sizeof(unsigned int);
        create_info.pCode = reinterpret_cast<const uint32_t*>(code.get_byte_code().data());

        if(vkCreateShaderModule(device.device, &create_info, nullptr, &backend) != VK_SUCCESS)
            throw std::runtime_error("Failed to create shader module");
    }

    void VulkanShaderModule::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;

        vkDestroyShaderModule(device.device, backend, nullptr);

        mark_destroyed();
    }
}
