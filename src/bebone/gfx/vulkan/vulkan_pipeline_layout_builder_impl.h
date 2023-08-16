#ifndef _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_BUILDER_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_BUILDER_IMPLEMENTATION_H_

#include <cassert>

#include "../device_impl.h"

#include "../pipeline_layout_builder_impl.h"

#include "vulkan_descriptor_pool.h"
#include "vulkan_pipeline_layout_impl.h"

/*
    // Pipeline layout builder atomatically insuers that all buffers have been craeted with proper count
    PipelineLayoutBuilder pipelineLayoutBuilder = renderer.create_pipeline_layout_builder();

        // x.add_uniform_buffer(binding, size)
        pipelineLayoutBuilder.bind_uniform_buffer(0, sizeof(float));
        pipelineLayoutBuilder.bind_uniform_buffer(1, sizeof(float) * 2);

    PipelineLayout pipelineLayout = pipelineLayoutBuilder.build();

*/

namespace bebone::gfx {
    class VulkanPipelineLayoutBuilderImpl : public PipelineLayoutBuilderImpl {
        private:
            DeviceImpl& _device;
            std::shared_ptr<VulkanDescriptorPool> _descriptorPool;
            const size_t _fif;

            VkDescriptorSetLayout descriptorSetLayout;

        public:
            VulkanPipelineLayoutBuilderImpl(const size_t& fif, DeviceImpl& device) : _device(device), _fif(fif) {
                _descriptorPool = std::make_shared<VulkanDescriptorPool>(device, 2);
            }

            ~VulkanPipelineLayoutBuilderImpl() {

            }

            void bind_uniform_buffer(const size_t& binding, UniformBuffer& buffer) override {
                VkDescriptorSetLayoutBinding uboLayoutBinding{};
                uboLayoutBinding.binding = binding;
                uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                uboLayoutBinding.descriptorCount = 1;
                uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
                uboLayoutBinding.pImmutableSamplers = nullptr; // Optional

                // Descriptor set
                VkDescriptorSetLayoutCreateInfo layoutInfo{};
                layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
                layoutInfo.bindingCount = 1;
                layoutInfo.pBindings = &uboLayoutBinding;

                if (vkCreateDescriptorSetLayout(_device.device(), &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create descriptor set layout!");
                }

                for(size_t i = 0; i < buffer.get_impl_size(); ++i) {
                    VulkanUniformBufferImpl* buf = static_cast<VulkanUniformBufferImpl*>(buffer.get_impl(i));

                    VkDescriptorSet* descriptorSet = _descriptorPool->create_descriptor(&descriptorSetLayout, buf->get_buffer());
                    buf->bind_descriptor_set(descriptorSet);
                }
            }

            PipelineLayout build() override {
                return PipelineLayout::create_from_impl<VulkanPipelineLayoutImpl>(_device, _descriptorPool, descriptorSetLayout);
            }
    };
}

#endif