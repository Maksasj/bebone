#include "vulkan_descriptor_set.h"

#include "vulkan_device.h"
#include "vulkan_descriptor_pool.h"
#include "vulkan_descriptor_set_layout.h"

namespace bebone::gfx {
    VulkanDescriptorSet::VulkanDescriptorSet(
        IVulkanDevice& device,
        VulkanDescriptorPool& descriptor_pool,
        const std::unique_ptr<VulkanDescriptorSetLayout>& descriptor_set_layout
    ) : device_owner(device) {
        VkDescriptorSetAllocateInfo alloc_info{};
        alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        alloc_info.descriptorPool = descriptor_pool.descriptor_pool;
        alloc_info.descriptorSetCount = 1;
        alloc_info.pSetLayouts = &descriptor_set_layout->descriptor_set_layout;

        VkDescriptorSetVariableDescriptorCountAllocateInfoEXT count_info;
        count_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO_EXT;
        count_info.pNext = nullptr;

        // Todo
        static unsigned int max_binding = 65536 - 1;
        count_info.descriptorSetCount = 1;

        count_info.pDescriptorCounts = &max_binding;
        alloc_info.pNext = &count_info; // Todo

        if (vkAllocateDescriptorSets(device_owner.get_vk_device(), &alloc_info, &descriptor_set) != VK_SUCCESS) {
            LOG_ERROR("Failed to allocate descriptor sets");
            throw std::runtime_error("failed to allocate descriptor sets!");
        }

        LOG_TRACE("Allocated Descriptor set");
    }

    // Todo add buffer_info offset there
void VulkanDescriptorSet::update_descriptor_set(
        IVulkanBuffer& buffer,
        const size_t& binding,
        const size_t& dst_array_element
    ) {
        VkDescriptorBufferInfo buffer_info{};
        buffer_info.buffer = buffer.get_vk_buffer();
        buffer_info.offset = 0;
        buffer_info.range = buffer.get_size();

        VkWriteDescriptorSet descriptor_write{};
        descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;

        descriptor_write.dstSet = descriptor_set;
        descriptor_write.dstBinding = binding;
        descriptor_write.dstArrayElement = dst_array_element;
        // Todo, remember that this mean \/
        // Todo THIS IS A HANDLE, and handle counter should work per shader binding, not a cpu binding thing

        descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptor_write.descriptorCount = 1;
        descriptor_write.pBufferInfo = &buffer_info;

        descriptor_write.pImageInfo = nullptr; // Optional
        descriptor_write.pTexelBufferView = nullptr; // Optional

        vkUpdateDescriptorSets(device_owner.get_vk_device(), 1, &descriptor_write, 0, nullptr);
    }

    void VulkanDescriptorSet::update_descriptor_set(
        IVulkanSampler& sampler,
        IVulkanImageView& view,
        const size_t& binding,
        const size_t& dst_array_element
    ) {
        VkDescriptorImageInfo image_info{};
        image_info.sampler = sampler.get_vk_image_sampler();
        image_info.imageView = view.get_vk_image_view();
        image_info.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL; // Todo, remove this hard coded cringe

        VkWriteDescriptorSet descriptor_write{};
        descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;

        descriptor_write.dstSet = descriptor_set;
        descriptor_write.dstBinding = binding;
        descriptor_write.dstArrayElement = dst_array_element; // Todo THIS IS A HANDLE, and handle counter should work per shader binding, not a cpu binding thing

        descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptor_write.descriptorCount = 1;
        // descriptorWrite.pBufferInfo = &buffer_info;
        descriptor_write.pImageInfo = &image_info;

        // descriptorWrite.pImageInfo = nullptr; // Optional
        descriptor_write.pTexelBufferView = nullptr; // Optional

        vkUpdateDescriptorSets(device_owner.get_vk_device(), 1, &descriptor_write, 0, nullptr);
    }
}
