#ifndef _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_BUILDER_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_BUILDER_IMPLEMENTATION_H_

#include <cassert>

#include "../device_impl.h"

#include "../pipeline_layout_builder_impl.h"

#include "vulkan_descriptor_pool.h"
#include "vulkan_pipeline_layout_impl.h"

namespace bebone::gfx {
    class VulkanDescriptorSetLayoutBlueprint {
        public:
            const size_t _binding;
            std::vector<VulkanBufferImpl*> _buffer;
            VkDescriptorType _type;

            VulkanDescriptorSetLayoutBlueprint(
                const size_t& binding,
                const VkDescriptorType& type, 
                const std::vector<VulkanBufferImpl*>& buffer) : _binding(binding), _buffer(buffer), _type(type) {
                    
            }
    };

    class VulkanPipelineLayoutBuilderImpl : public PipelineLayoutBuilderImpl {
        private:
            DeviceImpl& _device;
            const size_t _fif;

            std::vector<VulkanDescriptorSetLayoutBlueprint> descriptorSetLayoutsBlueprints;
            size_t descriptorsInNeed;

        public:
            VulkanPipelineLayoutBuilderImpl(const size_t& fif, DeviceImpl& device) : _device(device), _fif(fif), descriptorsInNeed(0) {

            }

            ~VulkanPipelineLayoutBuilderImpl() {

            }

            void bind_uniform_buffer(const size_t& binding, UniformBuffer& buffer) override {
                std::vector<VulkanBufferImpl*> buffers;

                for(size_t i = 0; i < buffer.get_impl_size(); ++i) {
                    VulkanBufferImpl* buf = static_cast<VulkanBufferImpl*>(buffer.get_impl(i));
                    buffers.push_back(buf);
                    ++descriptorsInNeed;
                }

                /*
                
                Look into dif, looks like that
                there is no need to create
                descriptorSetLayoutsBlueprints 
                for each implementations of buffer,
                even why do we need to do this lol ?
                
                */
               
                descriptorSetLayoutsBlueprints.push_back(VulkanDescriptorSetLayoutBlueprint(binding, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, buffers));
            }

            PipelineLayout build() override {
                std::shared_ptr<VulkanDescriptorPool> descriptorPool = std::make_shared<VulkanDescriptorPool>(_device, descriptorsInNeed);

                for(auto& descriptorBlueprint : descriptorSetLayoutsBlueprints) {
                    VkDescriptorSetLayout* descriptorSetLayout = descriptorPool->create_descriptor_set_layout(descriptorBlueprint._binding, descriptorBlueprint._type);

                    // Making descriptor for every buffer
                    for(auto& buffer : descriptorBlueprint._buffer) {
                        VkDescriptorSet* descriptorSet = descriptorPool->create_descriptor(descriptorSetLayout, buffer->get_buffer());

                        // Todo refactor this cringe
                        if(descriptorBlueprint._type == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER) {
                            VulkanUniformBufferImpl* uniformBufferImpl = static_cast<VulkanUniformBufferImpl*>(buffer);

                            uniformBufferImpl->bind_descriptor_set(descriptorSet);
                        }
                    }
                }

                return PipelineLayout::create_from_impl<VulkanPipelineLayoutImpl>(_device, descriptorPool);
            }
    };
}

#endif
