#ifndef _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_BUILDER_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_BUILDER_IMPLEMENTATION_H_

#include <cassert>

#include "../device_impl.h"

#include "../pipeline_layout_builder_impl.h"

#include "vulkan_descriptor_pool.h"
#include "vulkan_pipeline_layout_impl.h"

namespace bebone::gfx {
    class VulkanPipelineLayoutBuilderImpl : public PipelineLayoutBuilderImpl {
        private:
            DeviceImpl& _device;
            std::vector<VkPushConstantRange> constantRanges;

        public:
            VulkanPipelineLayoutBuilderImpl(DeviceImpl& device) : _device(device) {
            }

            ~VulkanPipelineLayoutBuilderImpl() {

            }

            void set_constant_range(const size_t& offset, const size_t& size) override {
                VkPushConstantRange pushConstant;
                pushConstant.offset = offset;
                pushConstant.size = size;
                pushConstant.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;

                constantRanges.push_back(pushConstant);
            }

            PipelineLayout build(GPUResourceManager& _gpuResourceManager) override {
                VulkanDescriptorPool& descriptorPool = _gpuResourceManager.get_descriptor_pool();
                return PipelineLayout::create_from_impl<VulkanPipelineLayoutImpl>(_device, descriptorPool, constantRanges);
            }
    };
}

#endif