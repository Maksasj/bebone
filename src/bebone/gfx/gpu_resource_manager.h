#ifndef _BEBONE_GFX_GPU_RESOURCE_MANAGER_H_
#define _BEBONE_GFX_GPU_RESOURCE_MANAGER_H_

#include "gfx_backend.h"

#include "vulkan/vulkan_descriptor_pool.h"
#include "vulkan/vulkan_command_buffer.h"
#include "uniform_buffer.h"

namespace bebone::gfx {
    class GPUResourceSet {
        private:
            std::vector<VkDescriptorSet*> descriptorSets;

        public:
            GPUResourceSet(std::vector<VkDescriptorSet*> _descriptorSets) : descriptorSets(_descriptorSets) {

            }

            void bind(VulkanCommandBuffer& commandBuffer, VulkanPipelineLayoutImpl& pipelineLayout, const size_t& frameIndex) {
                // Todo resolve this

                commandBuffer.bind_descriptor_set(pipelineLayout, *descriptorSets[frameIndex]);
            }

            VkDescriptorSet* get_descriptor(const size_t& index) {
                return descriptorSets[index];
            }
    };

    class GPUResourceSetBlueprint {
        private:
            const size_t _fif;
            VulkanDescriptorPool& _descriptorPool;
            std::vector<VkDescriptorSetLayoutBinding> bindings;

        public:
            GPUResourceSetBlueprint(const size_t fif, VulkanDescriptorPool& descriptorPool) : _fif(fif), _descriptorPool(descriptorPool) {
                
            }

            GPUResourceSetBlueprint& set_texture_resource(const size_t& binding) {
                VkDescriptorSetLayoutBinding layoutBinding{};
                layoutBinding.binding = binding;
                layoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
                layoutBinding.descriptorCount = 65536; // Todo this is max thing

                layoutBinding.stageFlags = VK_SHADER_STAGE_ALL; // Todo this should be confiruble
                layoutBinding.pImmutableSamplers = nullptr; // Optional

                bindings.push_back(layoutBinding);

                return *this;
            }

            GPUResourceSetBlueprint& add_uniform_buffer_resource(const size_t& binding) {
                VkDescriptorSetLayoutBinding layoutBinding{};
                
                layoutBinding.binding = binding;
                layoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                layoutBinding.descriptorCount = 65536; // Todo this is max thing

                layoutBinding.stageFlags = VK_SHADER_STAGE_ALL; // Todo this should be confiruble
                layoutBinding.pImmutableSamplers = nullptr; // Optional

                bindings.push_back(layoutBinding);

                return *this;
            }

            GPUResourceSet build() {
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
            size_t availableTextureHandle;

            GPUResourceManager(const size_t& fif, VulkanDevice& device) : _fif(fif), _device(device), descriptorPool(device) {
                availableUniformHandle = 0;
                availableTextureHandle = 0;
            }

            VulkanDescriptorPool& get_descriptor_pool () {
                return descriptorPool;
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
                    
                    descriptorWrite.dstSet = *resourceSet.get_descriptor(i);
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

            template<class DataType>
            UniformBuffer<DataType> create_uniform_buffer(GPUResourceSet& resourceSet, const size_t& binding) {
                return UniformBuffer<DataType>(create_uniform_buffer_impl<DataType>(resourceSet, binding));
            }

            GPUResourceSetBlueprint create_resource_set() {
                return GPUResourceSetBlueprint(_fif, descriptorPool);
            }
    };
}
#endif
