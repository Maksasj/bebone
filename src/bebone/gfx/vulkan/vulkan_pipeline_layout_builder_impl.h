#ifndef _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_BUILDER_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_BUILDER_IMPLEMENTATION_H_

#include <cassert>

#include "vulkan_device.h"

#include "../pipeline_layout_builder_impl.h"

#include "vulkan_descriptor_pool.h"
#include "vulkan_pipeline_layout_impl.h"

namespace bebone::gfx {
    class VulkanPipelineLayoutBuilderImpl {
        private:
            VulkanDevice& _device;
            std::vector<VkPushConstantRange> constantRanges;

        public:
            VulkanPipelineLayoutBuilderImpl(VulkanDevice& device) : _device(device) {
            }

            ~VulkanPipelineLayoutBuilderImpl() {

            }

            VulkanPipelineLayoutBuilderImpl& set_constant_range(const size_t& offset, const size_t& size) {
                VkPushConstantRange pushConstant;
                pushConstant.offset = offset;
                pushConstant.size = size;
                pushConstant.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;

                constantRanges.push_back(pushConstant);

                return *this;
            }

            VulkanPipelineLayoutImpl build(GPUResourceManager& _gpuResourceManager) {
                VulkanDescriptorPool& descriptorPool = _gpuResourceManager.get_descriptor_pool();
                return VulkanPipelineLayoutImpl(_device, descriptorPool, constantRanges);
            }
    };
}

#endif