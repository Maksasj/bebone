#ifndef _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_IMPLEMENTATION_H_

#include "../device_impl.h"
#include "../gfx_backend.h"
#include "../pipeline_layout_impl.h"

#include "vulkan_descriptor_pool.h"

namespace bebone::gfx {
    class VulkanPipelineLayoutImpl : public PipelineLayoutImpl {
        private:
            DeviceImpl& _device;
            VkPipelineLayout pipelineLayout;

        public:
            VulkanPipelineLayoutImpl(DeviceImpl& device, VulkanDescriptorPool& descriptorPool, const std::vector<VkPushConstantRange>& constantRanges) : _device(device) {
                VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
                pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

                pipelineLayoutInfo.setLayoutCount = descriptorPool.get_layouts_count(); // This thing should be computed from creatated descriptor sets, for now there is just constants
                pipelineLayoutInfo.pSetLayouts = descriptorPool.get_layouts_data(); // This thing should be computed from creatated descriptor sets, for now there is just constants
                pipelineLayoutInfo.pushConstantRangeCount = constantRanges.size();
                pipelineLayoutInfo.pPushConstantRanges = constantRanges.data();

                if(vkCreatePipelineLayout(_device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
                    throw std::runtime_error("Failed to create pipeline layout");
                }
            }

            VkPipelineLayout get_layout() {
                return pipelineLayout;
            }

            ~VulkanPipelineLayoutImpl() {
                vkDestroyPipelineLayout(_device.device(), pipelineLayout, nullptr);
            }
    };
}

#endif
