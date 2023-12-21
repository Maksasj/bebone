#ifndef _BEBONE_GFX_GPU_RESOURCE_MANAGER_H_
#define _BEBONE_GFX_GPU_RESOURCE_MANAGER_H_

#include "gfx_backend.h"

#include "vulkan/vulkan_descriptor_pool.h"
#include "vulkan/vulkan_command_buffer.h"
#include "uniform_buffer.h"

namespace bebone::gfx {
    class GPUResourceSet {
        public:
            std::vector<VkDescriptorSet*> descriptorSets;

            GPUResourceSet(std::vector<VkDescriptorSet*> _descriptorSets) : descriptorSets(_descriptorSets) {

            }
    };

    class GPUResourceSetBlueprint {
        private:
            const size_t _fif;
            VulkanDescriptorPool& _descriptorPool;

        public:
            GPUResourceSetBlueprint(const size_t fif, VulkanDescriptorPool& descriptorPool) : _fif(fif), _descriptorPool(descriptorPool) {
                
            }

            GPUResourceSet build(std::vector<VkDescriptorSetLayoutBinding> bindings) {
                VkDescriptorSetLayout* descriptorLayout = _descriptorPool.create_descriptor_set_layout(bindings);

                std::vector<VkDescriptorSet*> descriptorSets;

                for(size_t f = 0; f < _fif; ++f) {
                    VkDescriptorSet* descriptorSet = _descriptorPool.create_descriptor_bindless(descriptorLayout);
                    descriptorSets.push_back(descriptorSet);
                }

                return GPUResourceSet(descriptorSets);
            }
    };

    class GPUResourceManager {
        public:
            const size_t _fif;

            VulkanDevice& _device;
            VulkanDescriptorPool descriptorPool;

            size_t availableUniformHandle;

            GPUResourceManager(const size_t& fif, VulkanDevice& device) : _fif(fif), _device(device), descriptorPool(device) {
                availableUniformHandle = 0;
            }

            template<class DataType>
            std::vector<VulkanUniformBufferImpl*> create_uniform_buffer_impl(GPUResourceSet& resourceSet, const size_t& binding) {
                std::vector<VulkanUniformBufferImpl*> bufferImpl(_fif, nullptr);

                for(size_t i = 0; i < _fif; ++i) {
                    bufferImpl[i] = new VulkanUniformBufferImpl(sizeof(DataType), _device, availableUniformHandle++); // Todo available handles should be refactored
                    // const UniformBufferHandle resourceHandle = bufferImpl[i]->get_handle();

                    VkDescriptorBufferInfo bufferInfo{};
                    bufferInfo.buffer = bufferImpl[i]->get_buffer();
                    bufferInfo.offset = 0;
                    bufferInfo.range = sizeof(DataType);

                    VkWriteDescriptorSet descriptorWrite{};
                    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                    
                    descriptorWrite.dstSet = *resourceSet.descriptorSets[i];
                    descriptorWrite.dstBinding = binding;
                    descriptorWrite.dstArrayElement = bufferImpl[i]->get_handle().index; // Todo THIS IS A HANDLE, and handle counter should work per shader binding, not a cpu binding thing

                    descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                    descriptorWrite.descriptorCount = 1;
                    descriptorWrite.pBufferInfo = &bufferInfo;

                    descriptorWrite.pImageInfo = nullptr; // Optional
                    descriptorWrite.pTexelBufferView = nullptr; // Optional

                    vkUpdateDescriptorSets(descriptorPool._device.device(), 1, &descriptorWrite, 0, nullptr);
                }

                return bufferImpl;
            }

            GPUResourceSetBlueprint create_resource_set() {
                return GPUResourceSetBlueprint(_fif, descriptorPool);
            }
    };
}
#endif
