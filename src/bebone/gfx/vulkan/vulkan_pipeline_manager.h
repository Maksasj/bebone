#ifndef BEBONE_VULKAN_PIPELINE_MANAGER_H
#define BEBONE_VULKAN_PIPELINE_MANAGER_H

#include "../gfx_backend.h"

#include "vulkan_device.h"
#include "vulkan_descriptor_pool.h"

namespace bebone::gfx::vulkan {
    class VulkanConstRange;

    class VulkanPipelineManager : private core::NonCopyable {
        private:
            std::shared_ptr<VulkanDescriptorPool> descriptor_pool;

        public:
            /*
            VulkanPipelineManager(std::shared_ptr<VulkanDevice>& device) {
                descriptor_pool = device->create_descriptor_pool();
            }

            tuple<std::vector<std::shared_ptr<VulkanDescriptorSet>>, std::shared_ptr<VulkanPipeline>> create_pipeline(std::shared_ptr<VulkanDevice>& device) {
                auto descriptorSetLayout = device->create_descriptor_set_layouts({
                                                             VulkanDescriptorSetLayoutBinding::bindless_uniform(0),
                                                             VulkanDescriptorSetLayoutBinding::bindless_uniform(1)
                                                     });
                auto descriptors = descriptor_pool->create_descriptors(device, descriptorSetLayout[0], 3);

                auto pipelineLayout = device->create_pipeline_layout(descriptorSetLayout, {
                        VulkanConstRange::common(sizeof(Handles), 0)
                });
                auto vertShaderModule = device->create_shader_module("vert.glsl", ShaderTypes::VERTEX_SHADER);
                auto fragShaderModule = device->create_shader_module("frag.glsl", ShaderTypes::FRAGMENT_SHADER);
                auto pipeline = device->create_pipeline(swapChain, pipelineLayout, { vertShaderModule, fragShaderModule }, {
                        .pVertexInputState = { .vertexDescriptions = vertexDescriptions }
                });
            }
            */
    };
}

#endif
