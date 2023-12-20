#include "vulkan_command_buffer.h"
#include "vulkan_renderer_impl.h"

namespace bebone::gfx {
    VulkanCommandBuffer::VulkanCommandBuffer(const size_t& frameIndex) : _frameIndex(frameIndex) {

    }

    void VulkanCommandBuffer::begin_record() {
        VulkanBeginRecordCommand command(commandBuffer);
        command.execute();
    }

    void VulkanCommandBuffer::end_record() {
        VulkanEndRecordCommand command(commandBuffer);
        command.execute();
    }

    void VulkanCommandBuffer::begin_render_pass(std::shared_ptr<VulkanSwapChain>& swapChain, const u32& frameBuffer) {
        VulkanBeginRenderPassCommand command(commandBuffer, *swapChain, frameBuffer);
        command.execute();
    }

    void VulkanCommandBuffer::set_viewport(const i32& x, const i32& y, const u32& width, const u32& height) {
        VulkanSetViewportCommand command(commandBuffer, x, y, width, height);
        command.execute();
    }

    void VulkanCommandBuffer::end_render_pass() {
        VulkanEndRenderPassCommand command(commandBuffer);
        command.execute();
    }

    void VulkanCommandBuffer::bind_pipeline(VulkanPipeline& pipeline) {
        VulkanBindPipelineCommand command(commandBuffer, pipeline);
        command.execute();
    }

    void VulkanCommandBuffer::bind_index_buffer(IndexBuffer& indexBuffer) {
        VulkanBindIndexBufferCommand command(commandBuffer, *static_cast<VulkanIndexBufferImpl*>(indexBuffer.get_impl()));
        command.execute();
    }

    void VulkanCommandBuffer::draw(const size_t& vertexCount) {
        VulkanDrawCommand command(commandBuffer, vertexCount);
        command.execute();
    }

    void VulkanCommandBuffer::draw_indexed(const size_t& indexCount) {
        VulkanDrawIndexedCommand command(commandBuffer, indexCount);
        command.execute();
    }

    void VulkanCommandBuffer::bind_descriptor_set(VulkanPipelineLayoutImpl& pipelineLayout, VkDescriptorSet& descriptorSet) {
        VulkanBindDescriptorSet command(commandBuffer, &pipelineLayout, &descriptorSet);
        command.execute();
    }

    void VulkanCommandBuffer::push_constant(VulkanPipelineLayoutImpl& pipelineLayout, const uint32_t& size, const void* constantPtr) {
        VulkanPushConstant command(commandBuffer, &pipelineLayout, size, 0, constantPtr);
        command.execute();
    }

    void VulkanCommandBuffer::push_constant(VulkanPipelineLayoutImpl& pipelineLayout, const uint32_t& size, const size_t& offset, const void* constantPtr) {
        VulkanPushConstant command(commandBuffer, &pipelineLayout, size, offset, constantPtr);
        command.execute();
    }
}
