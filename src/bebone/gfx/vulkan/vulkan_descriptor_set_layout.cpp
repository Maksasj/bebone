#include "vulkan_descriptor_set_layout.h"
#include "vulkan_descriptor_set_layout_binding.h"

#include "vulkan_device.h"

namespace bebone::gfx::vulkan {
    VulkanDescriptorSetLayout::VulkanDescriptorSetLayout(VulkanDevice& device, const std::vector<VulkanDescriptorSetLayoutBinding>& allBindings) {
        std::vector<VkDescriptorBindingFlags> bindingFlags;
        std::vector<VkDescriptorSetLayoutBinding> bindings;

        for(const auto& b : allBindings)
            bindings.push_back(b.backend);

        for(size_t i = 0; i < bindings.size(); ++i) {
            VkDescriptorBindingFlags bindlessFlags;

            if(i == bindings.size() - 1) {
                bindlessFlags =
                        VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT_EXT |
                        // VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT_EXT |
                        VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT_EXT;
            } else {
                bindlessFlags =
                        VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT_EXT |
                        VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT_EXT;
            }

            bindingFlags.push_back(bindlessFlags);
        }

        // Descriptor set
        VkDescriptorSetLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = bindings.size();
        layoutInfo.pBindings = bindings.data();
        layoutInfo.flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT_EXT;

        VkDescriptorSetLayoutBindingFlagsCreateInfoEXT extendedInfo;
        extendedInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO_EXT;
        extendedInfo.pNext = nullptr;
        extendedInfo.bindingCount = bindingFlags.size();

        if(bindingFlags.size() == 0) {
            extendedInfo.pBindingFlags = nullptr;
        } else
            extendedInfo.pBindingFlags = bindingFlags.data();

        layoutInfo.pNext = &extendedInfo;

        if (vkCreateDescriptorSetLayout(device.device(), &layoutInfo, nullptr, &backend) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor set layout!");
        }
    }

    void VulkanDescriptorSetLayout::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;
            
        vkDestroyDescriptorSetLayout(device.device(), backend, nullptr);

        mark_destroyed();
    }
}