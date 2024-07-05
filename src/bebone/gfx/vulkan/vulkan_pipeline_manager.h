#ifndef _BEBONE_VULKAN_PIPELINE_MANAGER_H_
#define _BEBONE_VULKAN_PIPELINE_MANAGER_H_

#include "../gfx_backend.h"

#include "vulkan_device.h"
#include "vulkan_descriptor_pool.h"
#include "vulkan_pipeline_tuples.h"

namespace bebone::gfx {
    class VulkanConstRange;

    class VulkanPipelineManager : public VulkanApi, private core::NonCopyable {
        private:
            std::shared_ptr<VulkanDescriptorPool> descriptor_pool;
            std::vector<std::shared_ptr<VulkanDescriptorSetLayout>> descriptor_layouts;

        public:
            VulkanPipelineManager(VulkanDevice& device);

            VulkanManagedPipelineTuple create_pipeline(
                std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<VulkanRenderPass>& render_pass,
                const std::string& vertex_shader_file_path,
                const std::string& fragment_shader_file_path,
                const std::vector<VulkanConstRange>& constant_ranges,
                const std::vector<VulkanDescriptorSetLayoutBinding>& bindings,
                VulkanPipelineConfig config_info
            );

            void destroy(VulkanDevice& device) override;
    };
}

#endif
