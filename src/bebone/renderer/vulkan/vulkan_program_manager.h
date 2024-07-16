#ifndef _BEBONE_RENDERER_VULKAN_PROGRAM_MANAGER_H_
#define _BEBONE_RENDERER_VULKAN_PROGRAM_MANAGER_H_

#include "renderer_backend.h"
#include "../iprogram_manager.h"
#include "vulkan_program.h"
#include "vulkan_texture.h"

namespace bebone::renderer {
    class VulkanProgramManager : public IProgramManager {
        private:
            std::shared_ptr<VulkanDevice> device;
            std::shared_ptr<VulkanPipelineManager> pipeline_manager;
            std::vector<std::shared_ptr<VulkanProgram>> programs;

        public:
            VulkanProgramManager(const std::shared_ptr<VulkanDevice>& device) : device(device) {
                pipeline_manager = device->create_pipeline_manager();
            }

            std::shared_ptr<VulkanProgram> create_program(VulkanManagedPipelineTuple& pipeline) {
                auto program = std::make_shared<VulkanProgram>(pipeline);
                programs.push_back(program);
                return program;
            }

            void bind_bindless_texture(std::shared_ptr<renderer::VulkanTexture>& texture) {
                // Todo

                // for(auto& program : programs) {
                //     texture->gpu_handle = program->get_pipeline().bind_texture(device, texture->get_texture(), 0);
                //     std::cout << texture->gpu_handle << "\n";
                // }
            }

            std::shared_ptr<VulkanPipelineManager> get_pipeline_manager() const {
                return pipeline_manager;
            }
    };
}

#endif
