#include "gl_commands.h"

namespace bebone::gfx {
    OpenglBeginRenderPassCommand::OpenglBeginRenderPassCommand(CommandBuffer& commandBuffer, MyEngineSwapChain& swapChain) : BeginRenderPassCommand(commandBuffer, swapChain) {
        throw std::runtime_error("Not implemented");
    }

    void OpenglBeginRenderPassCommand::execute() {
        throw std::runtime_error("Not implemented");
    }

    OpenglEndRenderPassCommand::OpenglEndRenderPassCommand(CommandBuffer& commandBuffer) : EndRenderPassCommand(commandBuffer) {
        throw std::runtime_error("Not implemented");
    }

    void OpenglEndRenderPassCommand::execute()  {
        throw std::runtime_error("Not implemented");
    }

    OpenglBindPipelineCommand::OpenglBindPipelineCommand(CommandBuffer& commandBuffer, Pipeline& pipeline) : BindPipelineCommand(commandBuffer, pipeline) {
        throw std::runtime_error("Not implemented");
    }

    void OpenglBindPipelineCommand::execute() {
        throw std::runtime_error("Not implemented");
    }
}
