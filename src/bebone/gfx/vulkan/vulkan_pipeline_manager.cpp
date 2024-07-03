#include "vulkan_pipeline_manager.h"

#include <utility>

#include "vulkan_device.h"
#include "vulkan_descriptor_pool.h"
#include "vulkan_descriptor_set_layout.h"
#include "vulkan_descriptor_set_layout_binding.h"

namespace bebone::gfx {
    VulkanPipelineManager::VulkanPipelineManager(VulkanDevice& device) {
        descriptor_pool = device.create_descriptor_pool();
    }

    // Todo, actually swap chain is not needed there
    VulkanManagedPipelineTuple VulkanPipelineManager::create_pipeline(
        std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanSwapChain>& swap_chain,
        const std::string& vertex_shader_file_path,
        const std::string& fragment_shader_file_path,
        const std::vector<VulkanConstRange>& constant_ranges,
        const std::vector<VulkanDescriptorSetLayoutBinding>& bindings,
        VulkanPipelineConfig config_info
    ) {
        // Todo
        auto descriptor_set_layout = device->create_descriptor_set_layout(bindings);
        auto descriptors = descriptor_pool->create_descriptors(device, descriptor_set_layout, 3);

        auto pipeline_layout = device->create_pipeline_layout({ descriptor_set_layout }, constant_ranges);

        auto vert_shader_module = device->create_shader_module(vertex_shader_file_path, ShaderTypes::vertex_shader);
        auto frag_shader_module = device->create_shader_module(fragment_shader_file_path, ShaderTypes::fragment_shader);

        auto pipeline = device->create_pipeline(swap_chain, pipeline_layout, { vert_shader_module, frag_shader_module }, std::move(config_info));
        device->destroy_all(vert_shader_module, frag_shader_module);
        device->collect_garbage();

        descriptor_layouts.push_back(descriptor_set_layout);

        return { pipeline, pipeline_layout, descriptors };
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
