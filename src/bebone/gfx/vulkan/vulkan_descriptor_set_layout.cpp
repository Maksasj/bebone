#include "vulkan_descriptor_set_layout.h"
#include "vulkan_descriptor_set_layout_binding.h"

#include "vulkan_device.h"

namespace bebone::gfx {
    VulkanDescriptorSetLayout::VulkanDescriptorSetLayout(
        VulkanDevice& device,
        const std::vector<VulkanDescriptorSetLayoutBinding>& all_bindings
    ) : VulkanWrapper<VkDescriptorSetLayout>(device) {
        auto binding_flags = std::vector<VkDescriptorBindingFlags> {};
        binding_flags.reserve(all_bindings.size());

        auto bindings = std::vector<VkDescriptorSetLayoutBinding> {};
        bindings.reserve(all_bindings.size());

        for(const auto& b : all_bindings)
            bindings.push_back(b.backend);

        for(size_t i = 0; i < bindings.size(); ++i) {
            VkDescriptorBindingFlags flags;

            if(i == bindings.size() - 1) {
                flags =
                    VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT_EXT |
                    // VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT_EXT |
                    VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT_EXT;
            } else {
                flags =
                    VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT_EXT |
                    VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT_EXT;
            }

            binding_flags.push_back(flags);
        }

        // Descriptor set
        VkDescriptorSetLayoutCreateInfo layout_info{};
        layout_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layout_info.bindingCount = bindings.size();
        layout_info.pBindings = bindings.data();
        layout_info.flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT_EXT;

        VkDescriptorSetLayoutBindingFlagsCreateInfoEXT extended_info;
        extended_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO_EXT;
        extended_info.pNext = nullptr;
        extended_info.bindingCount = binding_flags.size();

        if(binding_flags.empty())
            extended_info.pBindingFlags = nullptr;
        else
            extended_info.pBindingFlags = binding_flags.data();

        layout_info.pNext = &extended_info;

        if(vkCreateDescriptorSetLayout(device.device, &layout_info, nullptr, &backend) != VK_SUCCESS)
            throw std::runtime_error("failed to create descriptor set layout!");
    }

    VulkanDescriptorSetLayout::~VulkanDescriptorSetLayout() {
        vkDestroyDescriptorSetLayout(device.device, backend, nullptr);
    }

    /*
    void VulkanDescriptorSetLayout::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;
            
        vkDestroyDescriptorSetLayout(device.device, backend, nullptr);

        mark_destroyed();
    }
    */
}