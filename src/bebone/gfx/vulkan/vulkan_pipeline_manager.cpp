#include "vulkan_pipeline_manager.h"

#include "vulkan_device.h"
#include "vulkan_descriptor_pool.h"
#include "vulkan_descriptor_set_layout.h"
#include "vulkan_descriptor_set_layout_binding.h"

namespace bebone::gfx::vulkan {
    VulkanPipelineManager::VulkanPipelineManager(VulkanDevice& device) {
        descriptor_pool = device.create_descriptor_pool();

    }

    VulkanManagedPipelineTuple VulkanPipelineManager::create_pipeline(
        std::shared_ptr<VulkanDevice>& device,
        std::shared_ptr<VulkanSwapChain>& swapChain,
        const std::string& vertex_shader_file_path,
        const std::string& fragment_shader_file_path,
        const std::vector<VulkanConstRange>& constantRanges,
        const std::vector<VulkanDescriptorSetLayoutBinding>& bindings,
        VulkanPipelineConfig configInfo
    ) {
        // Todo
        auto descriptorSetLayout = device->create_descriptor_set_layout(bindings);
        auto descriptors = descriptor_pool->create_descriptors(device, descriptorSetLayout, 3);

        auto pipelineLayout = device->create_pipeline_layout({ descriptorSetLayout }, constantRanges);

        auto vertShaderModule = device->create_shader_module(vertex_shader_file_path, ShaderTypes::vertex_shader);
        auto fragShaderModule = device->create_shader_module(fragment_shader_file_path, ShaderTypes::fragment_shader);

        auto pipeline = device->create_pipeline(swapChain, pipelineLayout, { vertShaderModule, fragShaderModule }, configInfo);
        device->destroy_all(vertShaderModule, fragShaderModule);
        device->collect_garbage();

        descriptor_layouts.push_back(descriptorSetLayout);

        return { pipeline, pipelineLayout, descriptors };
    }

    void VulkanPipelineManager::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;

        for(auto& layout : descriptor_layouts)
            layout->destroy(device);

        descriptor_pool->destroy(device);

        mark_destroyed();
    }
}
