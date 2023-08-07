#include "vulkan_command_buffer.h"
#include "vulkan_commands.h"

namespace bebone::gfx {
    VulkanCommandBuffer::VulkanCommandBuffer() : arena(_BEBONE_MEMORY_BYTES_8KB_) {
        
    }

    void VulkanCommandBuffer::begin_record() {
        VulkanBeginRecordCommand* ptr = static_cast<VulkanBeginRecordCommand*>(arena.alloc(sizeof(VulkanBeginRecordCommand)));
        (void*) new (ptr) VulkanBeginRecordCommand(*this);
    }

    void VulkanCommandBuffer::end_record() {
        VulkanEndRecordCommand* ptr = static_cast<VulkanEndRecordCommand*>(arena.alloc(sizeof(VulkanEndRecordCommand)));
        (void*) new (ptr) VulkanEndRecordCommand(*this);
    }

    void VulkanCommandBuffer::begin_render_pass(MyEngineSwapChain& swapChain, int frameBuffer) {
        VulkanBeginRenderPassCommand* ptr = static_cast<VulkanBeginRenderPassCommand*>(arena.alloc(sizeof(VulkanBeginRenderPassCommand)));
        (void*) new (ptr) VulkanBeginRenderPassCommand(*this, swapChain, frameBuffer);
    }

    void VulkanCommandBuffer::end_render_pass() {
        VulkanEndRenderPassCommand* ptr = static_cast<VulkanEndRenderPassCommand*>(arena.alloc(sizeof(VulkanEndRenderPassCommand)));
        (void*) new (ptr) VulkanEndRenderPassCommand(*this);
    }

    void VulkanCommandBuffer::bind_pipeline(std::shared_ptr<Pipeline>& pipeline) {
        VulkanBindPipelineCommand* ptr = static_cast<VulkanBindPipelineCommand*>(arena.alloc(sizeof(VulkanBindPipelineCommand)));
        (void*) new (ptr) VulkanBindPipelineCommand(*this, *pipeline);
    }

    void VulkanCommandBuffer::bind_buffer(std::shared_ptr<VertexBuffer>& vertexBuffer) {
        VulkanBindBufferCommand* ptr = static_cast<VulkanBindBufferCommand*>(arena.alloc(sizeof(VulkanBindBufferCommand)));
        (void*) new (ptr) VulkanBindBufferCommand(*this, *static_cast<VulkanVertexBuffer*>(vertexBuffer.get()));
    }

    void VulkanCommandBuffer::draw(const size_t& vertexCount) {
        VulkanDrawCommand* ptr = static_cast<VulkanDrawCommand*>(arena.alloc(sizeof(VulkanDrawCommand)));
        (void*) new (ptr) VulkanDrawCommand(*this, vertexCount);
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
