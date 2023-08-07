#ifndef _BEBONE_GFX_VULKAN_VULKAN_COMMANDS_H_
#define _BEBONE_GFX_VULKAN_VULKAN_COMMANDS_H_

#include <array>

#include "vulkan_vertex_buffer.h"

#include "../command.h"
#include "../swap_chain.h"
#include "../pipeline.h"

namespace bebone::gfx {

    class VulkanBeginRecordCommand : public Command {
        private:
            VulkanCommandBuffer& _commandBuffer;

        public:
            VulkanBeginRecordCommand(VulkanCommandBuffer& commandBuffer) : _commandBuffer(commandBuffer) {
                
            }

            void execute() override {
                VkCommandBufferBeginInfo beginInfo{};
                beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

                if(vkBeginCommandBuffer(_commandBuffer.commandBuffer, &beginInfo) != VK_SUCCESS) {
                    throw std::runtime_error("failed to being recording command buffer");
                }
            }
    };

    class VulkanEndRecordCommand : public Command {
        private:
            VulkanCommandBuffer& _commandBuffer;

        public:
            VulkanEndRecordCommand(VulkanCommandBuffer& commandBuffer) : _commandBuffer(commandBuffer) {

            }

            void execute() override {
                if (vkEndCommandBuffer(_commandBuffer.commandBuffer) != VK_SUCCESS) {
                    throw std::runtime_error("failed to end command buffer");
                }
            }
    };

    class VulkanBeginRenderPassCommand : public Command {
        private:
            VulkanCommandBuffer& _commandBuffer;
            MyEngineSwapChain& _swapChain;
            int _frameBuffer;

        public:
            VulkanBeginRenderPassCommand(VulkanCommandBuffer& commandBuffer, MyEngineSwapChain& swapChain, int frameBuffer) : _commandBuffer(commandBuffer), _swapChain(swapChain) {
                _frameBuffer = frameBuffer;
            }

            void execute() override {
                VkRenderPassBeginInfo renderPassInfo{};
                renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
                renderPassInfo.renderPass = _swapChain.getRenderPass();
                renderPassInfo.framebuffer = _swapChain.getFrameBuffer(_frameBuffer);
                
                renderPassInfo.renderArea.offset = {0, 0};
                renderPassInfo.renderArea.extent = _swapChain.getSwapChainExtent();
                
                std::array<VkClearValue, 2> clearValues{};
                clearValues[0].color = {{ 0.1f, 0.1f, 0.1f, 1.0f }};
                clearValues[1].depthStencil = { 1.0f, 0 };
                
                renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
                renderPassInfo.pClearValues = clearValues.data();
        
                vkCmdBeginRenderPass(_commandBuffer.commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
            }
    };

    class VulkanEndRenderPassCommand : public Command {
        private:
            VulkanCommandBuffer& _commandBuffer;

        public:
            VulkanEndRenderPassCommand(VulkanCommandBuffer& commandBuffer) : _commandBuffer(commandBuffer) {

            }

            void execute() override {
                vkCmdEndRenderPass(_commandBuffer.commandBuffer);
            }
    };

    class VulkanBindPipelineCommand : public Command {
        private:
            VulkanCommandBuffer& _commandBuffer;
            Pipeline& _pipeline;

        public:
            VulkanBindPipelineCommand(VulkanCommandBuffer& commandBuffer, Pipeline& pipeline) : _commandBuffer(commandBuffer), _pipeline(pipeline) {

            }

            void execute() override {
                vkCmdBindPipeline(_commandBuffer.commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipeline.grapgicsPipeline);
            }
    };

    class VulkanBindBufferCommand : public Command {
        private:
            VulkanCommandBuffer& _commandBuffer;
            VulkanVertexBuffer& _vertexBuffer;

        public:
            VulkanBindBufferCommand(VulkanCommandBuffer& commandBuffer, VulkanVertexBuffer& vertexBuffer) : _commandBuffer(commandBuffer), _vertexBuffer(vertexBuffer) {

            }

            void execute() override {
                VkBuffer buffers[] = {_vertexBuffer.get_buffer()};
                VkDeviceSize offset[] = {0};
                vkCmdBindVertexBuffers(_commandBuffer.commandBuffer, 0, 1, buffers, offset);
            }
    };

    class VulkanDrawCommand : public Command {
        private:
            VulkanCommandBuffer& _commandBuffer;
            const size_t _vertexCount;

        public:
            VulkanDrawCommand(VulkanCommandBuffer& commandBuffer, const size_t& vertexCount) : _commandBuffer(commandBuffer), _vertexCount(vertexCount) {

            }

            void execute() override {
                vkCmdDraw(_commandBuffer.commandBuffer, _vertexCount, 1, 0, 0);
            }
    };
}

#endif
