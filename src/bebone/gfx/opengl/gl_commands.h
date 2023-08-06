#ifndef _BEBONE_GFX_OPENGL_COMMANDS_H_
#define _BEBONE_GFX_OPENGL_COMMANDS_H_

#include "../gfx_backend.h"
#include "../commands.h"

#include "../pipeline.h"

namespace bebone::gfx {
    class OpenglBeginRenderPassCommand : public BeginRenderPassCommand {
        public:
            OpenglBeginRenderPassCommand(CommandBuffer& commandBuffer, MyEngineSwapChain& swapChain);

            void execute() override;
    };

    class OpenglEndRenderPassCommand : public EndRenderPassCommand {
        public:
            OpenglEndRenderPassCommand(CommandBuffer& commandBuffer);

            void execute() override;
    };

    class OpenglBindPipelineCommand : public BindPipelineCommand {
        public:
            OpenglBindPipelineCommand(CommandBuffer& commandBuffer, Pipeline& pipeline);

            void execute() override;
    };
}

#endif
