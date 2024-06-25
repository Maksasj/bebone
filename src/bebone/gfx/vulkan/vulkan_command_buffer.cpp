#include "vulkan_command_buffer.h"

#include "vulkan_device.h"
#include "vulkan_pipeline_layout.h"
#include "vulkan_command_buffer_pool.h"
#include "vulkan_descriptor_set.h"

namespace bebone::gfx::vulkan {
    VulkanCommandBuffer::VulkanCommandBuffer(std::shared_ptr<VulkanDevice>& device, VulkanCommandBufferPool& command_buffer_pool) {
        VkCommandBufferAllocateInfo alloc_info{};

        alloc_info.type = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        alloc_info.commandPool = command_buffer_pool.backend;
        alloc_info.command_bufferCount = static_cast<uint32_t>(1);

        if(vkAllocateCommandBuffers(device->device, &alloc_info, &backend) != VK_SUCCESS) {
            throw std::runtime_error("Failed to allocate command buffers !");
        }
    }

    VulkanCommandBuffer& VulkanCommandBuffer::begin_record() {
        VkCommandBufferBeginInfo begin_info{};

        begin_info.type = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if(vkBeginCommandBuffer(backend, &begin_info) != VK_SUCCESS)
            throw std::runtime_error("failed to being recording command buffer");

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::end_record() {
        if(vkEndCommandBuffer(backend) != VK_SUCCESS)
            throw std::runtime_error("failed to end command buffer");

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::begin_render_pass(
        const std::shared_ptr<VulkanSwapChain>& swap_chain,
        const u32& frame_buffer
    ) {
        VkRenderPassBeginInfo render_pass_info{};

        render_pass_info.type = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        render_pass_info.render_pass = swap_chain->render_target->render_pass->backend;
        render_pass_info.framebuffer = swap_chain->render_target->swapChainFramebuffers[frame_buffer]->backend;

        render_pass_info.renderArea.offset = {0, 0};
        render_pass_info.renderArea.extent = swap_chain->extent; // Todo not sure is extent is right, maybe there should be extent of render target

        // Todo
        std::array<VkClearValue, 2> clear_values{};
        clear_values[0].color = {{ 0.2f, 0.2f, 0.2f, 1.0f }};
        clear_values[1].depthStencil = { 1.0f, 0 };

        render_pass_info.clearValueCount = static_cast<uint32_t>(clear_values.size());
        render_pass_info.pClearValues = clear_values.data();

        vkCmdBeginRenderPass(backend, &render_pass_info, VK_SUBPASS_CONTENTS_INLINE);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::set_viewport(
        const i32& x,
        const i32& y,
        const u32& width,
        const u32& height
    ) {
        VkViewport viewport;

        viewport.x = static_cast<float>(x);
        viewport.y = static_cast<float>(y);
        viewport.width = static_cast<float>(width);
        viewport.height = static_cast<float>(height);

        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;   // Todo for now this set as default

        VkRect2D scissor = {{x, y}, {width, height}};

        vkCmdSetViewport(backend, 0, 1, &viewport);
        vkCmdSetScissor(backend, 0, 1, &scissor);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::end_render_pass() {
        vkCmdEndRenderPass(backend);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_pipeline(const VulkanPipeline& pipeline) {
        vkCmdBindPipeline(backend, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.backend);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_pipeline(const std::shared_ptr<VulkanPipeline>& pipeline) {
        vkCmdBindPipeline(backend, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->backend);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_vertex_buffer(const std::shared_ptr<VulkanBuffer>& buffer) {
        VkBuffer buffers[] = {buffer->backend};
        VkDeviceSize offset[] = { 0 }; // Todo

        vkCmdBindVertexBuffers(backend, 0, 1, buffers, offset);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_index_buffer(const std::shared_ptr<VulkanBuffer>& buffer) {
        // Todo, note that VK_INDEX_TYPE_UINT32 should match index size, akka for int should be used VK_INDEX_TYPE_UINT32
        vkCmdBindIndexBuffer(backend, buffer->backend, 0, VK_INDEX_TYPE_UINT32);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::draw(const size_t& vertex_count) {
        vkCmdDraw(backend, vertex_count, 1, 0, 0);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::draw_indexed(const size_t& index_count) {
        vkCmdDrawIndexed(backend, static_cast<uint32_t>(index_count), 1, 0, 0, 0);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_descriptor_set(
        const std::shared_ptr<VulkanPipelineLayout>& pipeline_layout,
        const std::shared_ptr<VulkanDescriptorSet>& descriptor_set
    ) {
        vkCmdBindDescriptorSets(backend, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline_layout->get_layout(), 0, 1, &descriptor_set->backend, 0, nullptr);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_descriptor_set(
        const std::shared_ptr<VulkanPipelineLayout>& pipeline_layout,
        const std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptor_sets,
        const size_t& frame
    ) {
        vkCmdBindDescriptorSets(backend, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline_layout->get_layout(), 0, 1, &descriptor_sets[frame]->backend, 0, nullptr);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_descriptor_sets(
        const std::shared_ptr<VulkanPipelineLayout>& pipeline_layout,
        const std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptor_sets
    ) {
        auto sets = std::vector<VkDescriptorSet> { };
        sets.reserve();

        for(const auto& descriptor : descriptor_sets)
            sets.push_back(descriptor->backend);

        vkCmdBindDescriptorSets(backend, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline_layout->get_layout(), 0, sets.size(), sets.data(), 0, nullptr);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::push_constant(
        const std::shared_ptr<VulkanPipelineLayout>& pipeline_layout,
        const uint32_t& size,
        const void* ptr
    ) {
        vkCmdPushConstants(backend, pipeline_layout->get_layout(), VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, size, ptr); // Todo, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::push_constant(
        const std::shared_ptr<VulkanPipelineLayout>& pipeline_layout,
        const uint32_t& size,
        const size_t& offset,
        const void* ptr
    ) {
        vkCmdPushConstants(backend, pipeline_layout->get_layout(), VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, offset, size, ptr); // Todo, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT

        return *this;
    }

    void VulkanCommandBuffer::destroy(VulkanDevice&) {
        // Todo
    }
}
