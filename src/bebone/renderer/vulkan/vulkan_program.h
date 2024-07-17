#ifndef _BEBONE_RENDERER_VULKAN_PROGRAM_H_
#define _BEBONE_RENDERER_VULKAN_PROGRAM_H_

#include "../iprogram.h"
#include "vulkan_command_encoder.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanProgram : public IProgram {
        private:
            std::shared_ptr<VulkanPipeline> pipeline;

        public:
            VulkanProgram(const std::shared_ptr<VulkanPipeline>& pipeline);

            void bind(ICommandEncoder* encoder) override;

            std::shared_ptr<VulkanPipeline>& get_pipeline();
    };
}

#endif
