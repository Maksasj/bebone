#ifndef _BEBONE_GFX_VULKAN_VULKAN_COMMANDS_H_
#define _BEBONE_GFX_VULKAN_VULKAN_COMMANDS_H_

#include <array>

#include "vulkan_vertex_buffer_impl.h"
#include "vulkan_index_buffer_impl.h"
#include "vulkan_uniform_buffer_impl.h"

#include "vulkan_pipeline_impl.h"
#include "vulkan_pipeline_layout_impl.h"

#include "../command.h"
#include "vulkan_swap_chain.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanBeginRecordCommand : public Command {
        private:
            VkCommandBuffer& _commandBuffer;

        public:
            VulkanBeginRecordCommand(VkCommandBuffer& commandBuffer) : _commandBuffer(commandBuffer) {
                
            }

            void execute() override {
                VkCommandBufferBeginInfo beginInfo{};
                beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

                if(vkBeginCommandBuffer(_commandBuffer, &beginInfo) != VK_SUCCESS) {
                    throw std::runtime_error("failed to being recording command buffer");
                }
            }
    };

    class VulkanEndRecordCommand : public Command {
        private:
            VkCommandBuffer& _commandBuffer;

        public:
            VulkanEndRecordCommand(VkCommandBuffer& commandBuffer) : _commandBuffer(commandBuffer) {

            }

            void execute() override {
                if (vkEndCommandBuffer(_commandBuffer) != VK_SUCCESS) {
                    throw std::runtime_error("failed to end command buffer");
                }
            }
    };

    class VulkanBeginRenderPassCommand : public Command {
        private:
            VkCommandBuffer& _commandBuffer;

            VulkanSwapChain& _swapChain;
            u32 _frameBuffer;

        public:
            VulkanBeginRenderPassCommand(VkCommandBuffer& commandBuffer, VulkanSwapChain& swapChain, const u32& frameBuffer) : _commandBuffer(commandBuffer), _swapChain(swapChain) {
                _frameBuffer = frameBuffer;
            }

            void execute() override {
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
    };

    class VulkanSetViewportCommand : public Command {
        private:
            VkCommandBuffer& _commandBuffer;

            const i32 _x;
            const i32 _y;
            const u32 _width;
            const u32 _height;

        public:
            VulkanSetViewportCommand(VkCommandBuffer& commandBuffer, const i32& x, const i32& y, const u32& width, const u32& height) 
                : _commandBuffer(commandBuffer), _x(x), _y(y), _width(width), _height(height) {

            }

            void execute() override {
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
    };

    class VulkanEndRenderPassCommand : public Command {
        private:
            VkCommandBuffer& _commandBuffer;

        public:
            VulkanEndRenderPassCommand(VkCommandBuffer& commandBuffer) : _commandBuffer(commandBuffer) {

            }

            void execute() override {
                vkCmdEndRenderPass(_commandBuffer);
            }
    };

    class VulkanBindPipelineCommand : public Command {
        private:
            VkCommandBuffer& _commandBuffer;
            VulkanPipeline& _pipeline;

        public:
            VulkanBindPipelineCommand(VkCommandBuffer& commandBuffer, VulkanPipeline& pipeline) : _commandBuffer(commandBuffer), _pipeline(pipeline) {

            }

            void execute() override {
                vkCmdBindPipeline(_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipeline.grapgicsPipeline);
            }
    };

    class VulkanBindVertexBufferCommand : public Command {
        private:
            VkCommandBuffer& _commandBuffer;
            VulkanBufferImpl& _buffer;

        public:
            VulkanBindVertexBufferCommand(VkCommandBuffer& commandBuffer, VulkanBufferImpl& buffer) : _commandBuffer(commandBuffer), _buffer(buffer) {

            }

            void execute() override {
                VkBuffer buffers[] = {_buffer.get_buffer()};
                VkDeviceSize offset[] = {0};
                vkCmdBindVertexBuffers(_commandBuffer, 0, 1, buffers, offset);
            }
    };

    class VulkanBindIndexBufferCommand : public Command {
        private:
            VkCommandBuffer& _commandBuffer;
            VulkanIndexBufferImpl& _indexBuffer;

        public:
            VulkanBindIndexBufferCommand(VkCommandBuffer& commandBuffer, VulkanIndexBufferImpl& indexBuffer) : _commandBuffer(commandBuffer), _indexBuffer(indexBuffer) {

            }

            void execute() override {
                // Todo, note that VK_INDEX_TYPE_UINT32 should match index size, akka for int should be used VK_INDEX_TYPE_UINT32
                vkCmdBindIndexBuffer(_commandBuffer, _indexBuffer.get_buffer(), 0, VK_INDEX_TYPE_UINT32);
            }
    };

    class VulkanDrawCommand : public Command {
        private:
            VkCommandBuffer& _commandBuffer;
            const size_t _vertexCount;

        public:
            VulkanDrawCommand(VkCommandBuffer& commandBuffer, const size_t& vertexCount) : _commandBuffer(commandBuffer), _vertexCount(vertexCount) {

            }

            void execute() override {
                vkCmdDraw(_commandBuffer, _vertexCount, 1, 0, 0);
            }
    };

    class VulkanDrawIndexedCommand : public Command {
        private:
            VkCommandBuffer& _commandBuffer;
            const size_t _indicesCount;

        public:
            VulkanDrawIndexedCommand(VkCommandBuffer& commandBuffer, const size_t& indicesCount) : _commandBuffer(commandBuffer), _indicesCount(indicesCount) {

            }

            void execute() override {
                vkCmdDrawIndexed(_commandBuffer, static_cast<uint32_t>(_indicesCount), 1, 0, 0, 0);
            }
    };

    class VulkanBindDescriptorSet : public Command {
        private:
            VkCommandBuffer& _commandBuffer;
            VkDescriptorSet* _descriptorSet;
            VulkanPipelineLayoutImpl* _pipelineLayout;

        public:
            VulkanBindDescriptorSet(VkCommandBuffer& commandBuffer, VulkanPipelineLayoutImpl* pipelineLayout, VkDescriptorSet* descriptorSet) 
                :   _commandBuffer(commandBuffer), 
                    _descriptorSet(descriptorSet),
                    _pipelineLayout(pipelineLayout) {

            }

            void execute() override {
                vkCmdBindDescriptorSets(_commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _pipelineLayout->get_layout(), 0, 1, _descriptorSet, 0, nullptr);
            }
    };

    class VulkanPushConstant : public Command {
        private:
            VkCommandBuffer& _commandBuffer;
            VulkanPipelineLayoutImpl* _pipelineLayout;

            const uint32_t _size;
            const uint32_t _offset;
            const void* _ptr;

        public:
            VulkanPushConstant(VkCommandBuffer& commandBuffer, VulkanPipelineLayoutImpl* pipelineLayout, const uint32_t& size, const uint32_t& offset, const void* ptr) 
                :   _commandBuffer(commandBuffer), 
                    _pipelineLayout(pipelineLayout),
                    _size(size),
                    _offset(offset),
                    _ptr(ptr) {

            }

            void execute() override {
                vkCmdPushConstants(_commandBuffer, _pipelineLayout->get_layout(), VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, _offset, _size, _ptr);
            }
    };
}

#endif
