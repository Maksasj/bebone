#ifndef _BEBONE_RENDERER_VULKAN_PROGRAM_MANAGER_H_
#define _BEBONE_RENDERER_VULKAN_PROGRAM_MANAGER_H_

#include "renderer_backend.h"
#include "../iprogram_manager.h"
#include "vulkan_program.h"

namespace bebone::renderer {
    class VulkanProgramManager : public IProgramManager {
        private:
            std::shared_ptr<VulkanPipelineManager> pipeline_manager;
            std::vector<std::shared_ptr<VulkanProgram>> programs;

        public:
            VulkanProgramManager(std::shared_ptr<VulkanDevice>& device) {
                pipeline_manager = device->create_pipeline_manager();
            }

            std::shared_ptr<VulkanProgram> create_program(VulkanManagedPipelineTuple& pipeline) {
                auto program = std::make_shared<VulkanProgram>(pipeline);
                programs.push_back(program);
                return program;
            }

            std::shared_ptr<VulkanPipelineManager> get_pipeline_manager() const {
                return pipeline_manager;
            }
    };
}

#endif
