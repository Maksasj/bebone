#include "vulkan_command_buffer.h"

#include "vulkan_device.h"
#include "vulkan_pipeline_layout.h"
#include "vulkan_command_buffer_pool.h"
#include "vulkan_descriptor_set.h"

namespace bebone::gfx {
    VulkanCommandBuffer::VulkanCommandBuffer(std::shared_ptr<VulkanDevice>& device, VulkanCommandBufferPool& command_buffer_pool) {
        VkCommandBufferAllocateInfo alloc_info{};

        alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        alloc_info.commandPool = command_buffer_pool.backend;
        alloc_info.commandBufferCount = static_cast<uint32_t>(1); // Todo

        if(vkAllocateCommandBuffers(device->device, &alloc_info, &backend) != VK_SUCCESS)
            throw std::runtime_error("Failed to allocate command buffers !");
    }

    VulkanCommandBuffer::VulkanCommandBuffer(VulkanDevice& device, VulkanCommandBufferPool& command_buffer_pool) {
        VkCommandBufferAllocateInfo alloc_info{};

        alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        alloc_info.commandPool = command_buffer_pool.backend;
        alloc_info.commandBufferCount = static_cast<uint32_t>(1); // Todo

        if(vkAllocateCommandBuffers(device.device, &alloc_info, &backend) != VK_SUCCESS)
            throw std::runtime_error("Failed to allocate command buffers !");
    }

    VulkanCommandBuffer& VulkanCommandBuffer::begin_record() {
        VkCommandBufferBeginInfo begin_info{};

        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if(vkBeginCommandBuffer(backend, &begin_info) != VK_SUCCESS)
            throw std::runtime_error("failed to being recording command buffer");

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::end_record() {
        if(vkEndCommandBuffer(backend) != VK_SUCCESS)
            throw std::runtime_error("failed to end command buffer");

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::begin_render_pass(const std::shared_ptr<VulkanSwapChain> swap_chain) {
        const auto& frame = swap_chain->get_current_frame();

        begin_render_pass(
            swap_chain->render_target->framebuffers[frame],
            swap_chain->render_pass);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::begin_render_pass(
        const std::shared_ptr<VulkanRenderTarget>& render_target,
        const std::shared_ptr<VulkanRenderPass>& render_pass,
        const size_t& frame
    ) {
        begin_render_pass(
            render_target->framebuffers[frame],
            render_pass);

        return *this;
    }

    // This function should have multiple variants, with swap chain or just with custom render target
    VulkanCommandBuffer& VulkanCommandBuffer::begin_render_pass(
        const std::shared_ptr<VulkanFramebuffer>& framebuffer,
        const std::shared_ptr<VulkanRenderPass>& render_pass
    ) {
        VkRenderPassBeginInfo render_pass_info{};
        render_pass_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        render_pass_info.renderPass = render_pass->backend;
        render_pass_info.framebuffer = framebuffer->backend;
        render_pass_info.renderArea.offset = {0, 0};
        render_pass_info.renderArea.extent = render_pass->get_extent(); // Todo not sure is extent is right, maybe there should be extent of render target

        // Collect all clear values
        auto clear_values = std::vector<VkClearValue> {};
        clear_values.reserve(render_pass->get_attachments().size());

        for(const auto& attachment : render_pass->get_attachments()) {
            if(attachment.type == Color)
                clear_values.push_back({ .color = { 0.2f, 0.2f, 0.2f, 1.0f } }); // Todo clear values should be allowed to be changet
            else if(attachment.type == Depth)
                clear_values.push_back({ .depthStencil = { 1.0f, 0 }}); // Todo clear values should be allowed to be changet
        }

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

        VkRect2D scissor = {{x, y}, { width, height }};

        vkCmdSetViewport(backend, 0, 1, &viewport);
        vkCmdSetScissor(backend, 0, 1, &scissor);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::end_render_pass() {
        vkCmdEndRenderPass(backend);

        return *this;
    }

    // Todo VK_PIPELINE_BIND_POINT_GRAPHICS should be configured
    VulkanCommandBuffer& VulkanCommandBuffer::bind_pipeline(const VulkanPipeline& pipeline) {
        vkCmdBindPipeline(backend, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.backend);

        return *this;
    }

    // Todo VK_PIPELINE_BIND_POINT_GRAPHICS should be configured
    VulkanCommandBuffer& VulkanCommandBuffer::bind_pipeline(const std::shared_ptr<VulkanPipeline>& pipeline) {
        vkCmdBindPipeline(backend, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->backend);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_vertex_buffer(const std::shared_ptr<VulkanBuffer>& buffer) {
        VkBuffer buffers[] = { buffer->backend };
        VkDeviceSize offset[] = { 0 }; // Todo

        vkCmdBindVertexBuffers(backend, 0, 1, buffers, offset);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_vertex_buffer(const std::shared_ptr<VulkanBufferMemoryTuple>& tuple) {
        return bind_vertex_buffer(tuple->buffer);
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_index_buffer(const std::shared_ptr<VulkanBuffer>& buffer) {
        // Todo, note that VK_INDEX_TYPE_UINT32 should match index size, akka for int should be used VK_INDEX_TYPE_UINT32
        vkCmdBindIndexBuffer(backend, buffer->backend, 0, VK_INDEX_TYPE_UINT32);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_index_buffer(const std::shared_ptr<VulkanBufferMemoryTuple>& tuple) {
        return bind_index_buffer(tuple->buffer);
    }

    VulkanCommandBuffer& VulkanCommandBuffer::draw(const size_t& vertex_count) {
        vkCmdDraw(backend, vertex_count, 1, 0, 0);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::draw_indexed(const size_t& index_count) {
        vkCmdDrawIndexed(backend, static_cast<uint32_t>(index_count), 1, 0, 0, 0);

        return *this;
    }

    // Todo VK_PIPELINE_BIND_POINT_GRAPHICS should be configured
    VulkanCommandBuffer& VulkanCommandBuffer::bind_descriptor_set(
        const std::shared_ptr<VulkanPipelineLayout>& pipeline_layout,
        const std::shared_ptr<VulkanDescriptorSet>& descriptor_set
    ) {
        vkCmdBindDescriptorSets(backend, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline_layout->backend, 0, 1, &descriptor_set->backend, 0, nullptr);

        return *this;
    }

    // Todo VK_PIPELINE_BIND_POINT_GRAPHICS should be configured
    VulkanCommandBuffer& VulkanCommandBuffer::bind_descriptor_set(
        const std::shared_ptr<VulkanPipelineLayout>& pipeline_layout,
        const std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptor_sets,
        const size_t& frame
    ) {
        vkCmdBindDescriptorSets(backend, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline_layout->backend, 0, 1, &descriptor_sets[frame]->backend, 0, nullptr);

        return *this;
    }

    // Todo VK_PIPELINE_BIND_POINT_GRAPHICS should be configured
    VulkanCommandBuffer& VulkanCommandBuffer::bind_descriptor_sets(
        const std::shared_ptr<VulkanPipelineLayout>& pipeline_layout,
        const std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptor_sets
    ) {
        auto sets = std::vector<VkDescriptorSet> { };
        sets.reserve(descriptor_sets.size());

        for(const auto& descriptor : descriptor_sets)
            sets.push_back(descriptor->backend);

        vkCmdBindDescriptorSets(backend, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline_layout->backend, 0, sets.size(), sets.data(), 0, nullptr);

        return *this;
    }

    // Todo VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT should be configured
    VulkanCommandBuffer& VulkanCommandBuffer::push_constant(
        const std::shared_ptr<VulkanPipelineLayout>& pipeline_layout,
        const u32& size,
        const void* ptr
    ) {
        vkCmdPushConstants(backend, pipeline_layout->backend, VK_SHADER_STAGE_ALL, 0, size, ptr); // Todo, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT

        return *this;
    }

    // Todo VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT should be configured
    VulkanCommandBuffer& VulkanCommandBuffer::push_constant(
        const std::shared_ptr<VulkanPipelineLayout>& pipeline_layout,
        const uint32_t& size,
        const size_t& offset,
        const void* ptr
    ) {
        vkCmdPushConstants(backend, pipeline_layout->backend, VK_SHADER_STAGE_ALL, offset, size, ptr); // Todo, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT

        return *this;
    }

    void VulkanCommandBuffer::destroy(VulkanDevice&) {
        // Todo
        
        mark_destroyed();
    }
}
