#ifndef _BEBONE_RENDERER_VULKAN_PROGRAM_H_
#define _BEBONE_RENDERER_VULKAN_PROGRAM_H_

#include "../iprogram.h"
#include "vulkan_command_encoder.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanProgram : public IProgram {
        private:
            VulkanManagedPipelineTuple pipeline;

        public:
            VulkanProgram(const VulkanManagedPipelineTuple& pipeline);

            void bind(ICommandEncoder* encoder) override;

            VulkanManagedPipelineTuple& get_pipeline();
    };
}

#endif
