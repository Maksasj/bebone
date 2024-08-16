#ifndef _BEBONE_RENDERER_VULKAN_PROGRAM_MANAGER_H_
#define _BEBONE_RENDERER_VULKAN_PROGRAM_MANAGER_H_

#include "renderer_backend.h"
#include "iprogram_manager.h"
#include "vulkan_program.h"
#include "vulkan_texture_impl.h"
#include "ipass_impl.h"
#include "vulkan_pass_impl.h"

namespace bebone::renderer {
    class VulkanProgramManager : public IProgramManager {
        private:
            std::shared_ptr<VulkanDevice> device;
            std::shared_ptr<VulkanPipelineManager> pipeline_manager;

            std::vector<std::shared_ptr<IProgram>> programs;

        public:
            VulkanProgramManager(const std::shared_ptr<VulkanDevice>& device);

            std::shared_ptr<IProgram> create_program(const std::shared_ptr<IPassImpl>& impl, const std::string& vertex_shader_code, const std::string& fragment_shader_code) override;

            void bind_texture(std::shared_ptr<VulkanTextureImpl>& texture);

            [[nodiscard]] std::shared_ptr<VulkanPipelineManager> get_pipeline_manager() const;
            [[nodiscard]] std::shared_ptr<VulkanDescriptorSet> get_descriptor_set() const;
            [[nodiscard]] std::shared_ptr<VulkanDescriptorSetLayout> get_descriptor_set_layout() const;
            [[nodiscard]] std::shared_ptr<VulkanPipelineLayout> get_pipeline_layout() const;
    };
}

#endif
