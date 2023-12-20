#include "vulkan_commands.h"

#include "vulkan_swap_chain.h"
#include "vulkan_pipeline_impl.h"
#include "vulkan_pipeline_layout_impl.h"

namespace bebone::gfx {
    VulkanBeginRecordCommand::VulkanBeginRecordCommand(VkCommandBuffer& commandBuffer) : _commandBuffer(commandBuffer) {

    }

    void VulkanBeginRecordCommand::execute()  {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if(vkBeginCommandBuffer(_commandBuffer, &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to being recording command buffer");
        }
    }

    VulkanEndRecordCommand::VulkanEndRecordCommand(VkCommandBuffer& commandBuffer) : _commandBuffer(commandBuffer) {

    }

    void VulkanEndRecordCommand::execute()  {
        if (vkEndCommandBuffer(_commandBuffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to end command buffer");
        }
    }

    VulkanBeginRenderPassCommand::VulkanBeginRenderPassCommand(VkCommandBuffer& commandBuffer, VulkanSwapChain& swapChain, const u32& frameBuffer) : _commandBuffer(commandBuffer), _swapChain(swapChain) {
        _frameBuffer = frameBuffer;
    }

    void VulkanBeginRenderPassCommand::execute()  {
        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = _swapChain.renderTarget->renderPass.renderPass;
        renderPassInfo.framebuffer = _swapChain.renderTarget->swapChainFramebuffers[_frameBuffer];

        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = _swapChain.renderTarget->extent;

        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color = {{ 0.2f, 0.2f, 0.2f, 1.0f }};
        clearValues[1].depthStencil = { 1.0f, 0 };

        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(_commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
    }

    VulkanSetViewportCommand::VulkanSetViewportCommand(VkCommandBuffer& commandBuffer, const i32& x, const i32& y, const u32& width, const u32& height)
        : _commandBuffer(commandBuffer), _x(x), _y(y), _width(width), _height(height) {

    }

    void VulkanSetViewportCommand::execute()  {
        VkViewport viewport;

        viewport.x = static_cast<float>(_x);
        viewport.y = static_cast<float>(_y);
        viewport.width = static_cast<float>(_width);
        viewport.height = static_cast<float>(_height);

        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;   // Todo for now this set as default

        VkRect2D scissor = {{_x, _y}, {_width, _height}};

        vkCmdSetViewport(_commandBuffer, 0, 1, &viewport);
        vkCmdSetScissor(_commandBuffer, 0, 1, &scissor);
    }

    VulkanEndRenderPassCommand::VulkanEndRenderPassCommand(VkCommandBuffer& commandBuffer) : _commandBuffer(commandBuffer) {

    }

    void VulkanEndRenderPassCommand::execute()  {
        vkCmdEndRenderPass(_commandBuffer);
    }

    VulkanBindPipelineCommand::VulkanBindPipelineCommand(VkCommandBuffer& commandBuffer, VulkanPipeline& pipeline) : _commandBuffer(commandBuffer), _pipeline(pipeline) {

    }

    void VulkanBindPipelineCommand::execute()  {
        vkCmdBindPipeline(_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipeline.grapgicsPipeline);
    }

    VulkanBindVertexBufferCommand::VulkanBindVertexBufferCommand(VkCommandBuffer& commandBuffer, VulkanBufferImpl* buffer) : _commandBuffer(commandBuffer), _buffer(buffer) {

    }

    void VulkanBindVertexBufferCommand::execute()  {
        VkBuffer buffers[] = {_buffer->get_buffer()};
        VkDeviceSize offset[] = {0};
        vkCmdBindVertexBuffers(_commandBuffer, 0, 1, buffers, offset);
    }

    VulkanBindIndexBufferCommand::VulkanBindIndexBufferCommand(VkCommandBuffer& commandBuffer, VulkanBufferImpl& indexBuffer) : _commandBuffer(commandBuffer), _indexBuffer(indexBuffer) {

    }

    void VulkanBindIndexBufferCommand::execute()  {
        // Todo, note that VK_INDEX_TYPE_UINT32 should match index size, akka for int should be used VK_INDEX_TYPE_UINT32
        vkCmdBindIndexBuffer(_commandBuffer, _indexBuffer.get_buffer(), 0, VK_INDEX_TYPE_UINT32);
    }

    VulkanDrawCommand::VulkanDrawCommand(VkCommandBuffer& commandBuffer, const size_t& vertexCount) : _commandBuffer(commandBuffer), _vertexCount(vertexCount) {

    }

    void VulkanDrawCommand::execute()  {
        vkCmdDraw(_commandBuffer, _vertexCount, 1, 0, 0);
    }

    VulkanDrawIndexedCommand::VulkanDrawIndexedCommand(VkCommandBuffer& commandBuffer, const size_t& indicesCount) : _commandBuffer(commandBuffer), _indicesCount(indicesCount) {

    }

    void VulkanDrawIndexedCommand::execute()  {
        vkCmdDrawIndexed(_commandBuffer, static_cast<uint32_t>(_indicesCount), 1, 0, 0, 0);
    }

    VulkanBindDescriptorSet::VulkanBindDescriptorSet(VkCommandBuffer& commandBuffer, VulkanPipelineLayoutImpl* pipelineLayout, VkDescriptorSet* descriptorSet)
        :   _commandBuffer(commandBuffer),
            _descriptorSet(descriptorSet),
            _pipelineLayout(pipelineLayout) {

    }

    void VulkanBindDescriptorSet::execute()  {
        vkCmdBindDescriptorSets(_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout->get_layout(), 0, 1, _descriptorSet, 0, nullptr);
    }

    VulkanPushConstant::VulkanPushConstant(VkCommandBuffer& commandBuffer, VulkanPipelineLayoutImpl* pipelineLayout, const uint32_t& size, const uint32_t& offset, const void* ptr)
        :   _commandBuffer(commandBuffer),
            _pipelineLayout(pipelineLayout),
            _size(size),
            _offset(offset),
            _ptr(ptr) {

    }

    void VulkanPushConstant::execute()  {
        vkCmdPushConstants(_commandBuffer, _pipelineLayout->get_layout(), VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, _offset, _size, _ptr);
    }
}
