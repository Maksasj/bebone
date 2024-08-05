#ifndef _BEBONE_RENDERER_VULKAN_PROGRAM_H_
#define _BEBONE_RENDERER_VULKAN_PROGRAM_H_

#include "iprogram.h"
#include "vulkan_command_encoder.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanProgram : public IProgram {
        private:
            std::shared_ptr<VulkanPipeline> pipeline;

            // Reference to bindless pipeline layout
            std::shared_ptr<VulkanPipelineLayout> pipeline_layout;

        public:
            VulkanProgram(
                const std::shared_ptr<VulkanPipeline>& pipeline,
                const std::shared_ptr<VulkanPipelineLayout>& pipeline_layout);

            void bind(ICommandEncoder* encoder) override;

            std::shared_ptr<VulkanPipeline> get_pipeline();
            std::shared_ptr<VulkanPipelineLayout> get_pipeline_layout();
    };
}

#endif
