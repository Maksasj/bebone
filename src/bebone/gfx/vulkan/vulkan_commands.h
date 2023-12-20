#ifndef _BEBONE_GFX_VULKAN_VULKAN_COMMANDS_H_
#define _BEBONE_GFX_VULKAN_VULKAN_COMMANDS_H_

#include <array>

#include "../gfx_backend.h"
#include "../command.h"

// #include "vulkan_vertex_buffer_impl.h"
// #include "vulkan_index_buffer_impl.h"
// #include "vulkan_uniform_buffer_impl.h"
//
// #include "vulkan_pipeline_impl.h"
// #include "vulkan_pipeline_layout_impl.h"
//
// #include "../command.h"
// #include "vulkan_swap_chain.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanSwapChain;
    class VulkanPipeline;
    class VulkanBufferImpl;
    class VulkanPipelineLayoutImpl;

    class VulkanBeginRecordCommand : public Command {
        private:
            VkCommandBuffer& _commandBuffer;

        public:
            VulkanBeginRecordCommand(VkCommandBuffer& commandBuffer);

            void execute() override;
    };

    class VulkanEndRecordCommand : public Command {
        private:
            VkCommandBuffer& _commandBuffer;

        public:
            VulkanEndRecordCommand(VkCommandBuffer& commandBuffer);

            void execute() override;
    };

    class VulkanBeginRenderPassCommand : public Command {
        private:
            VkCommandBuffer& _commandBuffer;

            VulkanSwapChain& _swapChain;
            u32 _frameBuffer;

        public:
            VulkanBeginRenderPassCommand(VkCommandBuffer& commandBuffer, VulkanSwapChain& swapChain, const u32& frameBuffer);

            void execute() override;
    };

    class VulkanSetViewportCommand : public Command {
        private:
            VkCommandBuffer& _commandBuffer;

            const i32 _x;
            const i32 _y;
            const u32 _width;
            const u32 _height;

        public:
            VulkanSetViewportCommand(VkCommandBuffer& commandBuffer, const i32& x, const i32& y, const u32& width, const u32& height);

            void execute() override;
    };

    class VulkanEndRenderPassCommand : public Command {
        private:
            VkCommandBuffer& _commandBuffer;

        public:
            VulkanEndRenderPassCommand(VkCommandBuffer& commandBuffer);

            void execute() override;
    };

    class VulkanBindPipelineCommand : public Command {
        private:
            VkCommandBuffer& _commandBuffer;
            VulkanPipeline& _pipeline;

        public:
            VulkanBindPipelineCommand(VkCommandBuffer& commandBuffer, VulkanPipeline& pipeline);

            void execute() override;
    };

    class VulkanBindVertexBufferCommand : public Command {
        private:
            VkCommandBuffer& _commandBuffer;
            VulkanBufferImpl* _buffer;

        public:
            VulkanBindVertexBufferCommand(VkCommandBuffer& commandBuffer, VulkanBufferImpl* buffer);

            void execute() override;
    };

    class VulkanBindIndexBufferCommand : public Command {
        private:
            VkCommandBuffer& _commandBuffer;
            VulkanBufferImpl& _indexBuffer;

        public:
            VulkanBindIndexBufferCommand(VkCommandBuffer& commandBuffer, VulkanBufferImpl& indexBuffer);

            void execute() override;
    };

    class VulkanDrawCommand : public Command {
        private:
            VkCommandBuffer& _commandBuffer;
            const size_t _vertexCount;

        public:
            VulkanDrawCommand(VkCommandBuffer& commandBuffer, const size_t& vertexCount);

            void execute() override;
    };

    class VulkanDrawIndexedCommand : public Command {
        private:
            VkCommandBuffer& _commandBuffer;
            const size_t _indicesCount;

        public:
            VulkanDrawIndexedCommand(VkCommandBuffer& commandBuffer, const size_t& indicesCount);

            void execute() override;
    };

    class VulkanBindDescriptorSet : public Command {
        private:
            VkCommandBuffer& _commandBuffer;
            VkDescriptorSet* _descriptorSet;
            VulkanPipelineLayoutImpl* _pipelineLayout;

        public:
            VulkanBindDescriptorSet(VkCommandBuffer& commandBuffer, VulkanPipelineLayoutImpl* pipelineLayout, VkDescriptorSet* descriptorSet);

            void execute() override;
    };

    class VulkanPushConstant : public Command {
        private:
            VkCommandBuffer& _commandBuffer;
            VulkanPipelineLayoutImpl* _pipelineLayout;

            const uint32_t _size;
            const uint32_t _offset;
            const void* _ptr;

        public:
            VulkanPushConstant(VkCommandBuffer& commandBuffer, VulkanPipelineLayoutImpl* pipelineLayout, const uint32_t& size, const uint32_t& offset, const void* ptr);

            void execute() override;
    };
}

#endif
