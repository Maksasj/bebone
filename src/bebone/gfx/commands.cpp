#include "commands.h"

#include "vulkan/vulkan_commands.h"
#include "opengl/gl_commands.h"

namespace bebone::gfx {
    BeginRenderPassCommand::BeginRenderPassCommand(CommandBuffer& commandBuffer, MyEngineSwapChain& swapChain) : _commandBuffer(commandBuffer), _swapChain(swapChain) {

    }

    void BeginRenderPassCommand::push(CommandBuffer& commandBuffer, MyEngineSwapChain& swapChain) {
        BeginRenderPassCommand* ptr = static_cast<BeginRenderPassCommand*>(commandBuffer.push_bytes(sizeof(BeginRenderPassCommand)));

        switch (commandBuffer.get_api()) {
            case RenderingApi::OPENGL: new (ptr) OpenglBeginRenderPassCommand(commandBuffer, swapChain); break;
            case RenderingApi::VULKAN: new (ptr) VulkanBeginRenderPassCommand(commandBuffer, swapChain); break;
            case RenderingApi::NONE: throw std::runtime_error("api is not implemented"); break;
        }

        ptr->execute();
    }

    EndRenderPassCommand::EndRenderPassCommand(CommandBuffer& commandBuffer) : _commandBuffer(commandBuffer) {

    }

    void EndRenderPassCommand::push(CommandBuffer& commandBuffer) {
        EndRenderPassCommand* ptr = static_cast<EndRenderPassCommand*>(commandBuffer.push_bytes(sizeof(EndRenderPassCommand)));

        switch (commandBuffer.get_api()) {
            case RenderingApi::OPENGL: new (ptr) OpenglEndRenderPassCommand(commandBuffer); break;
            case RenderingApi::VULKAN: new (ptr) VulkanEndRenderPassCommand(commandBuffer); break;
            case RenderingApi::NONE: throw std::runtime_error("api is not implemented"); break;
        }

        ptr->execute();
    }

    BindPipelineCommand::BindPipelineCommand(CommandBuffer& commandBuffer, Pipeline& pipeline) : _commandBuffer(commandBuffer), _pipeline(pipeline) {

    }

    void BindPipelineCommand::push(CommandBuffer& commandBuffer, Pipeline& pipeline) {
        BindPipelineCommand* ptr = static_cast<BindPipelineCommand*>(commandBuffer.push_bytes(sizeof(BindPipelineCommand)));

        switch (commandBuffer.get_api()) {
            case RenderingApi::OPENGL: new (ptr) OpenglBindPipelineCommand(commandBuffer, pipeline); break;
            case RenderingApi::VULKAN: new (ptr) VulkanBindPipelineCommand(commandBuffer, pipeline); break;
            case RenderingApi::NONE: throw std::runtime_error("api is not implemented"); break;
        }

        ptr->execute();
    }
}
