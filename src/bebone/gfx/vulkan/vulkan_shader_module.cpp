#include "vulkan_shader_module.h"

#include "vulkan_device.h"

namespace bebone::gfx {
    VulkanShaderModule::VulkanShaderModule(VulkanDevice& device, const ShaderCode& code) : device_owner(device), type(code.get_shader_type()) {
        VkShaderModuleCreateInfo create_info{};

        create_info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        create_info.codeSize = code.get_byte_code().size() * sizeof(unsigned int);
        create_info.pCode = reinterpret_cast<const uint32_t*>(code.get_byte_code().data());

        if(vkCreateShaderModule(device.device, &create_info, nullptr, &backend) != VK_SUCCESS) {
            LOG_ERROR("Failed to create shader module");
            throw std::runtime_error("Failed to create shader module");
        }

        LOG_TRACE("Created Vulkan shader module");
    }

    VulkanShaderModule::~VulkanShaderModule() {
        vkDestroyShaderModule(device_owner.device, backend, nullptr);

        LOG_TRACE("Destroyed Vulkan shader module");
    }

    // void VulkanShaderModule::destroy(VulkanDevice& device) {
    //     if(is_destroyed())
    //         return;
//
    //     vkDestroyShaderModule(device.device, backend, nullptr);
//
    //     LOG_TRACE("Destroyed Vulkan shader module");
//
    //     mark_destroyed();
    // }
}
