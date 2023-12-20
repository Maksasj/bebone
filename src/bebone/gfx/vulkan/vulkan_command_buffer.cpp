#include "vulkan_command_buffer.h"
#include "vulkan_renderer_impl.h"

namespace bebone::gfx {
    VulkanCommandBuffer::VulkanCommandBuffer(const size_t& frameIndex) : arena(_BEBONE_MEMORY_BYTES_8KB_ * _BEBONE_MEMORY_BYTES_8KB_), _frameIndex(frameIndex) {

    }

    void VulkanCommandBuffer::begin_record() {
        VulkanBeginRecordCommand* ptrTarget = static_cast<VulkanBeginRecordCommand*>(arena.alloc(sizeof(VulkanBeginRecordCommand)));
        std::ignore = new (ptrTarget) VulkanBeginRecordCommand(commandBuffer);
    }

    void VulkanCommandBuffer::end_record() {
        VulkanEndRecordCommand* ptrTarget = static_cast<VulkanEndRecordCommand*>(arena.alloc(sizeof(VulkanEndRecordCommand)));
        std::ignore = new (ptrTarget) VulkanEndRecordCommand(commandBuffer);
    }

    void VulkanCommandBuffer::begin_render_pass(std::shared_ptr<VulkanSwapChain>& swapChain, const u32& frameBuffer) {
        VulkanBeginRenderPassCommand* ptrTarget = static_cast<VulkanBeginRenderPassCommand*>(arena.alloc(sizeof(VulkanBeginRenderPassCommand)));

        std::ignore = new (ptrTarget) VulkanBeginRenderPassCommand(commandBuffer, *swapChain, frameBuffer);
    }

    void VulkanCommandBuffer::set_viewport(const i32& x, const i32& y, const u32& width, const u32& height) {
        VulkanSetViewportCommand* ptrTarget = static_cast<VulkanSetViewportCommand*>(arena.alloc(sizeof(VulkanSetViewportCommand)));
        std::ignore = new (ptrTarget) VulkanSetViewportCommand(commandBuffer, x, y, width, height);
    }

    void VulkanCommandBuffer::end_render_pass() {
        VulkanEndRenderPassCommand* ptrTarget = static_cast<VulkanEndRenderPassCommand*>(arena.alloc(sizeof(VulkanEndRenderPassCommand)));
        std::ignore = new (ptrTarget) VulkanEndRenderPassCommand(commandBuffer);
    }

    void VulkanCommandBuffer::bind_pipeline(Pipeline& pipeline) {
        VulkanBindPipelineCommand* ptrTarget = static_cast<VulkanBindPipelineCommand*>(arena.alloc(sizeof(VulkanBindPipelineCommand)));

        VulkanPipeline* vulkanPipeline = pipeline.get_impl(); 

        std::ignore = new (ptrTarget) VulkanBindPipelineCommand(commandBuffer, *vulkanPipeline);
    }

    /*
    void VulkanCommandBuffer::bind_vertex_buffer(VertexBuffer& vertexBuffer) {
        VulkanBindVertexBufferCommand* ptrTarget = static_cast<VulkanBindVertexBufferCommand*>(arena.alloc(sizeof(VulkanBindVertexBufferCommand)));
        std::ignore = new (ptrTarget) VulkanBindVertexBufferCommand(commandBuffer, *static_cast<VulkanVertexBufferImpl*>(vertexBuffer.get_impl()));
    }
    */

    void VulkanCommandBuffer::bind_index_buffer(IndexBuffer& indexBuffer) {
        VulkanBindIndexBufferCommand* ptrTarget = static_cast<VulkanBindIndexBufferCommand*>(arena.alloc(sizeof(VulkanBindIndexBufferCommand)));
        std::ignore = new (ptrTarget) VulkanBindIndexBufferCommand(commandBuffer, *static_cast<VulkanIndexBufferImpl*>(indexBuffer.get_impl()));
    }

    void VulkanCommandBuffer::draw(const size_t& vertexCount) {
        VulkanDrawCommand* ptrTarget = static_cast<VulkanDrawCommand*>(arena.alloc(sizeof(VulkanDrawCommand)));
        std::ignore = new (ptrTarget) VulkanDrawCommand(commandBuffer, vertexCount);
    }

    void VulkanCommandBuffer::draw_indexed(const size_t& indexCount) {
        VulkanDrawIndexedCommand* ptrTarget = static_cast<VulkanDrawIndexedCommand*>(arena.alloc(sizeof(VulkanDrawIndexedCommand)));
        std::ignore = new (ptrTarget) VulkanDrawIndexedCommand(commandBuffer, indexCount);
    }

    void VulkanCommandBuffer::bind_descriptor_set(VulkanPipelineLayoutImpl& pipelineLayout, VkDescriptorSet& descriptorSet) {
        VulkanBindDescriptorSet* ptrTarget = static_cast<VulkanBindDescriptorSet*>(arena.alloc(sizeof(VulkanBindDescriptorSet)));
        VulkanPipelineLayoutImpl* pipelineLayoutImpl = &pipelineLayout;

        std::ignore = new (ptrTarget) VulkanBindDescriptorSet(commandBuffer, pipelineLayoutImpl, &descriptorSet); 
    }

    void VulkanCommandBuffer::push_constant(VulkanPipelineLayoutImpl& pipelineLayout, const uint32_t& size, const void* constantPtr) {
        VulkanPushConstant* ptrTarget = static_cast<VulkanPushConstant*>(arena.alloc(sizeof(VulkanPushConstant)));
        VulkanPipelineLayoutImpl* pipelineLayoutImpl = &pipelineLayout;

        std::ignore = new (ptrTarget) VulkanPushConstant(commandBuffer, pipelineLayoutImpl, size, 0, constantPtr); 
    }

    void VulkanCommandBuffer::push_constant(VulkanPipelineLayoutImpl& pipelineLayout, const uint32_t& size, const size_t& offset, const void* constantPtr) {
        VulkanPushConstant* ptrTarget = static_cast<VulkanPushConstant*>(arena.alloc(sizeof(VulkanPushConstant)));
        VulkanPipelineLayoutImpl* pipelineLayoutImpl = &pipelineLayout;

        std::ignore = new (ptrTarget) VulkanPushConstant(commandBuffer, pipelineLayoutImpl, size, offset, constantPtr); 
    }

    void VulkanCommandBuffer::preprocess() {

    }

    void VulkanCommandBuffer::submit() {
        const size_t& size = arena.size();

        for(size_t i = 0; i < size; ++i) {
            Command* command = static_cast<Command*>(arena.at(i));

            command->execute();
        }

        arena.clear(); // Todo I guess place of this thing should be changet
    }
}
