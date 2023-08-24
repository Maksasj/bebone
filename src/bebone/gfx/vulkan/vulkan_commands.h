#ifndef _BEBONE_GFX_VULKAN_VULKAN_COMMANDS_H_
#define _BEBONE_GFX_VULKAN_VULKAN_COMMANDS_H_

#include <array>

#include "vulkan_vertex_buffer_impl.h"
#include "vulkan_index_buffer_impl.h"
#include "../vulkan_uniform_buffer_impl.h"

#include "vulkan_pipeline_impl.h"
#include "vulkan_pipeline_layout_impl.h"

#include "../command.h"
#include "../swap_chain_impl.h"

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
            MyEngineSwapChainImpl& _swapChain;
            int _frameBuffer;

        public:
            VulkanBeginRenderPassCommand(VulkanCommandBuffer& commandBuffer, MyEngineSwapChainImpl& swapChain, int frameBuffer) : _commandBuffer(commandBuffer), _swapChain(swapChain) {
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
                clearValues[0].color = {{ 0.2f, 0.2f, 0.2f, 1.0f }};
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
            VulkanPipeline& _pipeline;

        public:
            VulkanBindPipelineCommand(VulkanCommandBuffer& commandBuffer, VulkanPipeline& pipeline) : _commandBuffer(commandBuffer), _pipeline(pipeline) {

            }

            void execute() override {
                vkCmdBindPipeline(_commandBuffer.commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipeline.grapgicsPipeline);
            }
    };

    class VulkanBindVertexBufferCommand : public Command {
        private:
            VulkanCommandBuffer& _commandBuffer;
            VulkanVertexBufferImpl& _vertexBuffer;

        public:
            VulkanBindVertexBufferCommand(VulkanCommandBuffer& commandBuffer, VulkanVertexBufferImpl& vertexBuffer) : _commandBuffer(commandBuffer), _vertexBuffer(vertexBuffer) {

            }

            void execute() override {
                VkBuffer buffers[] = {_vertexBuffer.get_buffer()};
                VkDeviceSize offset[] = {0};
                vkCmdBindVertexBuffers(_commandBuffer.commandBuffer, 0, 1, buffers, offset);
            }
    };

    class VulkanBindIndexBufferCommand : public Command {
        private:
            VulkanCommandBuffer& _commandBuffer;
            VulkanIndexBufferImpl& _indexBuffer;

        public:
            VulkanBindIndexBufferCommand(VulkanCommandBuffer& commandBuffer, VulkanIndexBufferImpl& indexBuffer) : _commandBuffer(commandBuffer), _indexBuffer(indexBuffer) {

            }

            void execute() override {
                // Todo, note that VK_INDEX_TYPE_UINT32 should match index size, akka for int should be used VK_INDEX_TYPE_UINT32
                vkCmdBindIndexBuffer(_commandBuffer.commandBuffer, _indexBuffer.get_buffer(), 0, VK_INDEX_TYPE_UINT32);
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

    class VulkanDrawIndexedCommand : public Command {
        private:
            VulkanCommandBuffer& _commandBuffer;
            const size_t _indicesCount;

        public:
            VulkanDrawIndexedCommand(VulkanCommandBuffer& commandBuffer, const size_t& indicesCount) : _commandBuffer(commandBuffer), _indicesCount(indicesCount) {

            }

            void execute() override {
                vkCmdDrawIndexed(_commandBuffer.commandBuffer, static_cast<uint32_t>(_indicesCount), 1, 0, 0, 0);
            }
    };

    class VulkanBindDescriptorSet : public Command {
        private:
            VulkanCommandBuffer& _commandBuffer;
            VkDescriptorSet* _descriptorSet;
            VulkanPipelineLayoutImpl* _pipelineLayout;

        public:
            VulkanBindDescriptorSet(VulkanCommandBuffer& commandBuffer, VulkanPipelineLayoutImpl* pipelineLayout, VkDescriptorSet* descriptorSet) 
                :   _commandBuffer(commandBuffer), 
                    _descriptorSet(descriptorSet),
                    _pipelineLayout(pipelineLayout) {

            }

            void execute() override {
                vkCmdBindDescriptorSets(_commandBuffer.commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout->get_layout(), 0, 1, _descriptorSet, 0, nullptr);
            }
    };

    class VulkanPushConstant : public Command {
        private:
            VulkanCommandBuffer& _commandBuffer;
            VulkanPipelineLayoutImpl* _pipelineLayout;

            const uint32_t _size;
            const void* _ptr;

        public:
            VulkanPushConstant(VulkanCommandBuffer& commandBuffer, VulkanPipelineLayoutImpl* pipelineLayout, const uint32_t& size, const void* ptr) 
                :   _commandBuffer(commandBuffer), 
                    _pipelineLayout(pipelineLayout),
                    _size(size),
                    _ptr(ptr) {

            }

            void execute() override {
                vkCmdPushConstants(_commandBuffer.commandBuffer, _pipelineLayout->get_layout(), VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, _size, _ptr);
            }
    };
}

#endif
