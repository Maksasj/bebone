#include "vulkan_command_buffer.h"
#include "vulkan_commands.h"

namespace bebone::gfx {
    VulkanCommandBuffer::VulkanCommandBuffer() : arena(_BEBONE_MEMORY_BYTES_8KB_) {
        
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

    void VulkanCommandBuffer::bind_buffer(VertexBuffer& vertexBuffer) {
        VulkanBindBufferCommand* ptr = static_cast<VulkanBindBufferCommand*>(arena.alloc(sizeof(VulkanBindBufferCommand)));
        std::ignore = new (ptr) VulkanBindBufferCommand(*this, *static_cast<VulkanVertexBufferImpl*>(vertexBuffer.get_impl()));
    }

    void VulkanCommandBuffer::draw(const size_t& vertexCount) {
        VulkanDrawCommand* ptr = static_cast<VulkanDrawCommand*>(arena.alloc(sizeof(VulkanDrawCommand)));
        std::ignore = new (ptr) VulkanDrawCommand(*this, vertexCount);
    }

    void VulkanCommandBuffer::preprocess() {

    }

    void VulkanCommandBuffer::submit() {
        const size_t size = arena.size();

        for(size_t i = 0; i < size; ++i) {
            Command* command = static_cast<Command*>(arena.at(i));

            command->execute();
        }
    }

    RenderingApi VulkanCommandBuffer::get_api() {
        return VULKAN;
    }
}
