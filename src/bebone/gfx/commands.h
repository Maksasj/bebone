#ifndef _BEBONE_GFX_COMMAND_H_
#define _BEBONE_GFX_COMMAND_H_

#include "command_buffer.h"
#include "gfx_backend.h"
#include "swap_chain.h"
#include "pipeline.h"

namespace bebone::gfx {
    class Command {
        public:
            virtual void execute() = 0;
    };

    class BeginRenderPassCommand : public Command {
        protected:
            CommandBuffer& _commandBuffer;
            MyEngineSwapChain& _swapChain;

        public:
            BeginRenderPassCommand(CommandBuffer& commandBuffer, MyEngineSwapChain& swapChain);

            static void push(CommandBuffer& commandBuffer, MyEngineSwapChain& swapChain);
    };

    class EndRenderPassCommand : public Command {
        protected:
            CommandBuffer& _commandBuffer;

        public:
            EndRenderPassCommand(CommandBuffer& commandBuffer);

            static void push(CommandBuffer& commandBuffer);
    };

    class BindPipelineCommand : public Command {
        protected:
            CommandBuffer& _commandBuffer;
            Pipeline& _pipeline;

        public:
            BindPipelineCommand(CommandBuffer& commandBuffer, Pipeline& pipeline);

            static void push(CommandBuffer& commandBuffer, Pipeline& pipeline);
    };
}

#endif
