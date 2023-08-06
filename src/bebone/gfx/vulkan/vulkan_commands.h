#ifndef _BEBONE_GFX_VULKAN_COMMANDS_H_
#define _BEBONE_GFX_VULKAN_COMMANDS_H_

#include <array>

#include "../gfx_backend.h"

#include "vulkan_command_buffer.h"
#include "../commands.h"

#include "../swap_chain.h"
#include "../pipeline.h"

namespace bebone::gfx {
    class VulkanBeginRenderPassCommand : public BeginRenderPassCommand {
        public:
            VulkanBeginRenderPassCommand(CommandBuffer& commandBuffer, MyEngineSwapChain& swapChain);

            void execute() override;
    };

    class VulkanEndRenderPassCommand : public EndRenderPassCommand {
        public:
            VulkanEndRenderPassCommand(CommandBuffer& commandBuffer);

            void execute() override;
    };


    class VulkanBindPipelineCommand : public BindPipelineCommand {
        public:
            VulkanBindPipelineCommand(CommandBuffer& commandBuffer, Pipeline& pipeline);

            void execute() override;
    };
}

#endif
