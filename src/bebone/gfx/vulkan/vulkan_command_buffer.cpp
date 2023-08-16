#include "vulkan_command_buffer.h"
#include "vulkan_commands.h"

namespace bebone::gfx {
    VulkanCommandBuffer::VulkanCommandBuffer(const size_t& frameIndex) : arena(_BEBONE_MEMORY_BYTES_8KB_), _frameIndex(frameIndex) {

    }

    void VulkanCommandBuffer::begin_record() {
        VulkanBeginRecordCommand* ptr = static_cast<VulkanBeginRecordCommand*>(arena.alloc(sizeof(VulkanBeginRecordCommand)));
        std::ignore = new (ptr) VulkanBeginRecordCommand(*this);
    }

    void VulkanCommandBuffer::end_record() {
        VulkanEndRecordCommand* ptr = static_cast<VulkanEndRecordCommand*>(arena.alloc(sizeof(VulkanEndRecordCommand)));
        std::ignore = new (ptr) VulkanEndRecordCommand(*this);
    }

    void VulkanCommandBuffer::begin_render_pass(MyEngineSwapChainImpl& swapChain, int frameBuffer) {
        VulkanBeginRenderPassCommand* ptr = static_cast<VulkanBeginRenderPassCommand*>(arena.alloc(sizeof(VulkanBeginRenderPassCommand)));
        std::ignore = new (ptr) VulkanBeginRenderPassCommand(*this, swapChain, frameBuffer);
    }

    void VulkanCommandBuffer::end_render_pass() {
        VulkanEndRenderPassCommand* ptr = static_cast<VulkanEndRenderPassCommand*>(arena.alloc(sizeof(VulkanEndRenderPassCommand)));
        std::ignore = new (ptr) VulkanEndRenderPassCommand(*this);
    }

    void VulkanCommandBuffer::bind_pipeline(Pipeline& pipeline) {
        VulkanBindPipelineCommand* ptr = static_cast<VulkanBindPipelineCommand*>(arena.alloc(sizeof(VulkanBindPipelineCommand)));
        std::ignore = new (ptr) VulkanBindPipelineCommand(*this, *static_cast<VulkanPipelineImpl*>(pipeline.get_impl()));
    }

    void VulkanCommandBuffer::bind_vertex_buffer(VertexBuffer& vertexBuffer) {
        VulkanBindVertexBufferCommand* ptr = static_cast<VulkanBindVertexBufferCommand*>(arena.alloc(sizeof(VulkanBindVertexBufferCommand)));
        std::ignore = new (ptr) VulkanBindVertexBufferCommand(*this, *static_cast<VulkanVertexBufferImpl*>(vertexBuffer.get_impl()));
    }

    void VulkanCommandBuffer::bind_index_buffer(IndexBuffer& indexBuffer) {
        VulkanBindIndexBufferCommand* ptr = static_cast<VulkanBindIndexBufferCommand*>(arena.alloc(sizeof(VulkanBindIndexBufferCommand)));
        std::ignore = new (ptr) VulkanBindIndexBufferCommand(*this, *static_cast<VulkanIndexBufferImpl*>(indexBuffer.get_impl()));
    }

    void VulkanCommandBuffer::draw(const size_t& vertexCount) {
        VulkanDrawCommand* ptr = static_cast<VulkanDrawCommand*>(arena.alloc(sizeof(VulkanDrawCommand)));
        std::ignore = new (ptr) VulkanDrawCommand(*this, vertexCount);
    }

    void VulkanCommandBuffer::draw_indexed(const size_t& indexCount) {
        VulkanDrawIndexedCommand* ptr = static_cast<VulkanDrawIndexedCommand*>(arena.alloc(sizeof(VulkanDrawIndexedCommand)));
        std::ignore = new (ptr) VulkanDrawIndexedCommand(*this, indexCount);
    }

    void VulkanCommandBuffer::bind_uniform_buffer(PipelineLayout& pipelineLayout, UniformBuffer& uniformBuffer) {
        VulkanBindDescriptorSet* ptr = static_cast<VulkanBindDescriptorSet*>(arena.alloc(sizeof(VulkanBindDescriptorSet)));
        VulkanPipelineLayoutImpl* pipelineLayoutImpl = static_cast<VulkanPipelineLayoutImpl*>(pipelineLayout.get_impl());
        VulkanUniformBufferImpl* uniformBufferImpl = static_cast<VulkanUniformBufferImpl*>(uniformBuffer.get_impl(_frameIndex));

        VkDescriptorSet* descriptorSet = uniformBufferImpl->get_descriptor_set();

        if(descriptorSet == nullptr) {
            throw std::runtime_error("failed to get descriptor, uniform buffer implementation in not binded with any descriptor");
        }

        std::ignore = new (ptr) VulkanBindDescriptorSet(*this, pipelineLayoutImpl, descriptorSet); 
    }

    void VulkanCommandBuffer::preprocess() {

    }

    void VulkanCommandBuffer::submit() {
        const size_t& size = arena.size();

        for(size_t i = 0; i < size; ++i) {
            Command* command = static_cast<Command*>(arena.at(i));

            command->execute();
        }
    }

    RenderingApi VulkanCommandBuffer::get_api() {
        return VULKAN;
    }
}
