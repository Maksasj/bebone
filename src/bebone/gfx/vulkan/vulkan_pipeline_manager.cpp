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
        std::shared_ptr<VulkanSwapChain>& swap_chain,
        const std::vector<VulkanConstRange>& constant_ranges,
        const std::vector<VulkanDescriptorSetLayoutBinding>& bindings,
        VulkanPipelineConfig config_info
    ) {
        // Todo
        auto descriptor_set_layout = device->create_descriptor_set_layouts(bindings);

        auto descriptors = descriptor_pool->create_descriptors(device, descriptor_set_layout[0], 3);

        auto pipeline_layout = device->create_pipeline_layout(descriptor_set_layout, constant_ranges);

        auto vert_shader_module = device->create_shader_module("vert.glsl", ShaderTypes::vertex_shader);
        auto frag_shader_module = device->create_shader_module("frag.glsl", ShaderTypes::fragment_shader);

        auto pipeline = device->create_pipeline(swap_chain, pipeline_layout, { vert_shader_module, frag_shader_module }, config_info);

        device->destroy_all(vert_shader_module, frag_shader_module);
        device->collect_garbage();

        return make_tuple(pipeline, pipeline_layout, descriptors);
    }

    void VulkanPipelineManager::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;

        descriptor_pool->destroy(device);

        mark_destroyed();
    }
}
