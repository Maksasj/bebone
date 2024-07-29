#ifndef _BEBONE_RENDERER_VULKAN_PROGRAM_MANAGER_H_
#define _BEBONE_RENDERER_VULKAN_PROGRAM_MANAGER_H_

#include "renderer_backend.h"
#include "iprogram_manager.h"
#include "vulkan_program.h"
#include "vulkan_texture.h"

namespace bebone::renderer {
    class VulkanProgramManager : public IProgramManager {
        private:
            std::shared_ptr<VulkanDevice> device;
            std::shared_ptr<VulkanPipelineManager> pipeline_manager;

            std::vector<std::shared_ptr<VulkanProgram>> programs;

        public:
            VulkanProgramManager(const std::shared_ptr<VulkanDevice>& device);

            std::shared_ptr<VulkanProgram> create_program(std::shared_ptr<VulkanPipeline>& pipeline);

            void bind_texture(std::shared_ptr<VulkanTexture>& texture);

            std::shared_ptr<VulkanPipelineManager> get_pipeline_manager() const;

            const std::shared_ptr<VulkanDescriptorSet>& get_descriptor_set() const;
            const std::shared_ptr<VulkanDescriptorSetLayout>& get_descriptor_set_layout() const;
            const std::shared_ptr<VulkanPipelineLayout>& get_pipeline_layout() const;
    };
}

#endif
