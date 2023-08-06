#include "vulkan_commands.h"

namespace bebone::gfx {
    VulkanBeginRenderPassCommand::VulkanBeginRenderPassCommand(CommandBuffer& commandBuffer, MyEngineSwapChain& swapChain) : BeginRenderPassCommand(commandBuffer, swapChain) {

    }

    void VulkanBeginRenderPassCommand::execute() {
        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = _swapChain.getRenderPass();
        renderPassInfo.framebuffer = _swapChain.getFrameBuffer(0);
        
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = _swapChain.getSwapChainExtent();
        
        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color = {{ 0.1f, 0.1f, 0.1f, 1.0f }};
        clearValues[1].depthStencil = { 1.0f, 0 };
        
        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        VkCommandBuffer& commnandBuffer = static_cast<VulkanCommandBuffer&>(_commandBuffer).commandBuffer; 

        vkCmdBeginRenderPass(commnandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    }

    VulkanEndRenderPassCommand::VulkanEndRenderPassCommand(CommandBuffer& commandBuffer) : EndRenderPassCommand(commandBuffer) {

    }

    void VulkanEndRenderPassCommand::execute() {
        VkCommandBuffer& commnandBuffer = static_cast<VulkanCommandBuffer&>(_commandBuffer).commandBuffer; 
        vkCmdEndRenderPass(commnandBuffer);
    }

    VulkanBindPipelineCommand::VulkanBindPipelineCommand(CommandBuffer& commandBuffer, Pipeline& pipeline) : BindPipelineCommand(commandBuffer, pipeline) {

    }

    void VulkanBindPipelineCommand::execute() {
        VkCommandBuffer& commnandBuffer = static_cast<VulkanCommandBuffer&>(_commandBuffer).commandBuffer; 
        _pipeline.bind(commnandBuffer);
    }
}
