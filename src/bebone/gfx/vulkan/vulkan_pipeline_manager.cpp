#include "vulkan_pipeline_manager.h"

#include "vulkan_device.h"
#include "vulkan_descriptor_pool.h"
#include "vulkan_descriptor_set_layout_binding.h"

namespace bebone::gfx::vulkan {
    VulkanPipelineManager::VulkanPipelineManager(VulkanDevice& device) {
        descriptor_pool = device.create_descriptor_pool();

    }

    VulkanManagedPipelineTuple VulkanPipelineManager::create_pipeline(
        std::shared_ptr<VulkanDevice>& device,
        std::shared_ptr<VulkanSwapChain>& swapChain,
        const std::vector<VulkanConstRange>& constantRanges,
        const std::vector<VulkanDescriptorSetLayoutBinding>& bindings,
        VulkanPipelineConfig configInfo
    ) {
        // Todo
        auto descriptorSetLayout = device->create_descriptor_set_layouts(bindings);

        auto descriptors = descriptor_pool->create_descriptors(device, descriptorSetLayout[0], 3);

        auto pipelineLayout = device->create_pipeline_layout(descriptorSetLayout, constantRanges);

        auto vertShaderModule = device->create_shader_module("vert.glsl", ShaderTypes::VERTEX_SHADER);
        auto fragShaderModule = device->create_shader_module("frag.glsl", ShaderTypes::FRAGMENT_SHADER);

        auto pipeline = device->create_pipeline(swapChain, pipelineLayout, { vertShaderModule, fragShaderModule }, configInfo);

        device->destroy_all(vertShaderModule, fragShaderModule);

        return make_tuple(pipeline, pipelineLayout, descriptors);
    }

    void VulkanPipelineManager::destroy(VulkanDevice& device) {
        descriptor_pool->destroy(device);
    }
}
