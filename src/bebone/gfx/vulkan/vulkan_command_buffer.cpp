#include "vulkan_command_buffer.h"

#include "vulkan_device.h"
#include "vulkan_pipeline_layout.h"
#include "vulkan_command_buffer_pool.h"
#include "vulkan_descriptor_set.h"
#include "vulkan_pipeline_tuples.h"

namespace bebone::gfx::vulkan {
    VulkanCommandBuffer::VulkanCommandBuffer(std::shared_ptr<VulkanDevice>& device, VulkanCommandBufferPool& commandBufferPool) {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = commandBufferPool.backend;
        allocInfo.commandBufferCount = static_cast<uint32_t>(1);

        if(vkAllocateCommandBuffers(device->device(), &allocInfo, &backend) != VK_SUCCESS) {
            throw std::runtime_error("Failed to allocate command buffers !");
        }
    }

    VulkanCommandBuffer& VulkanCommandBuffer::begin_record() {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if(vkBeginCommandBuffer(backend, &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to being recording command buffer");
        }

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::end_record() {
        if (vkEndCommandBuffer(backend) != VK_SUCCESS) {
            throw std::runtime_error("failed to end command buffer");
        }

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::begin_render_pass(std::shared_ptr<VulkanSwapChain>& swapChain, const u32& frameBuffer) {
        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = swapChain->renderTarget->renderPass->backend;
        renderPassInfo.framebuffer = swapChain->renderTarget->swapChainFramebuffers[frameBuffer]->backend;

        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = swapChain->extent; // Todo not sure is extent is right, maybe there should be extent of render target

        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color = {{ 0.2f, 0.2f, 0.2f, 1.0f }};
        clearValues[1].depthStencil = { 1.0f, 0 };

        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(backend, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::set_viewport(const i32& x, const i32& y, const u32& width, const u32& height) {
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

    VulkanCommandBuffer& VulkanCommandBuffer::bind_pipeline(VulkanPipeline& pipeline) {
        vkCmdBindPipeline(backend, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.backend);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_pipeline(std::shared_ptr<VulkanPipeline>& pipeline) {
        vkCmdBindPipeline(backend, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->backend);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_managed_pipeline(VulkanManagedPipelineTuple& tuple, const size_t& frame) {
        auto& [pipeline, pipelineLayout, descriptors] = tuple;
        return bind_pipeline(pipeline).bind_descriptor_set(pipelineLayout, descriptors, frame);
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_vertex_buffer(std::shared_ptr<VulkanBuffer>& buffer) {
        VkBuffer buffers[] = {buffer->backend};
        VkDeviceSize offset[] = {0};
        vkCmdBindVertexBuffers(backend, 0, 1, buffers, offset);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_index_buffer(std::shared_ptr<VulkanBuffer>& indexBuffer) {
        // Todo, note that VK_INDEX_TYPE_UINT32 should match index size, akka for int should be used VK_INDEX_TYPE_UINT32
        vkCmdBindIndexBuffer(backend, indexBuffer->backend, 0, VK_INDEX_TYPE_UINT32);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_vertex_buffer(VulkanBufferMemoryTuple& tuple) {
        return bind_vertex_buffer(tuple.buffer);
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_index_buffer(VulkanBufferMemoryTuple& tuple) {
        return bind_index_buffer(tuple.buffer);
    }

    VulkanCommandBuffer& VulkanCommandBuffer::draw(const size_t& vertexCount) {
        vkCmdDraw(backend, vertexCount, 1, 0, 0);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::draw_indexed(const size_t& indexCount) {
        vkCmdDrawIndexed(backend, static_cast<uint32_t>(indexCount), 1, 0, 0, 0);

        return *this;
    }


    VulkanCommandBuffer& VulkanCommandBuffer::bind_descriptor_set(std::shared_ptr<VulkanPipelineLayout>& pipelineLayout, std::shared_ptr<VulkanDescriptorSet>& descriptorSet) {
        vkCmdBindDescriptorSets(backend, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout->get_layout(), 0, 1, &descriptorSet->backend, 0, nullptr);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_descriptor_set(std::shared_ptr<VulkanPipelineLayout>& pipelineLayout, std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptorSets, const size_t& frame) {
        vkCmdBindDescriptorSets(backend, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout->get_layout(), 0, 1, &descriptorSets[frame]->backend, 0, nullptr);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_descriptor_sets(std::shared_ptr<VulkanPipelineLayout>& pipelineLayout, std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptorSets) {
        std::vector<VkDescriptorSet> sets;

        for(const auto& descriptor : descriptorSets)
            sets.push_back(descriptor->backend);

        vkCmdBindDescriptorSets(backend, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout->get_layout(), 0, sets.size(), sets.data(), 0, nullptr);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::push_constant(std::shared_ptr<VulkanPipelineLayout>& pipelineLayout, const uint32_t& size, const void* constantPtr) {
        vkCmdPushConstants(backend, pipelineLayout->get_layout(), VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, size, constantPtr);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::push_constant(std::shared_ptr<VulkanPipelineLayout>& pipelineLayout, const uint32_t& size, const size_t& offset, const void* constantPtr) {
        vkCmdPushConstants(backend, pipelineLayout->get_layout(), VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, offset, size, constantPtr);

        return *this;
    }

    void VulkanCommandBuffer::destroy(VulkanDevice&) {

    }
}
