#include "vulkan_command_buffer.h"
#include "vulkan_renderer_impl.h"

namespace bebone::gfx {
    VulkanCommandBuffer::VulkanCommandBuffer() {

    }

    VulkanCommandBuffer& VulkanCommandBuffer::begin_record() {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if(vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to being recording command buffer");
        }

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::end_record() {
        if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to end command buffer");
        }

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::begin_render_pass(std::shared_ptr<VulkanSwapChain>& swapChain, const u32& frameBuffer) {
        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = swapChain->renderTarget->renderPass.renderPass;
        renderPassInfo.framebuffer = swapChain->renderTarget->swapChainFramebuffers[frameBuffer];

        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = swapChain->renderTarget->extent;

        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color = {{ 0.2f, 0.2f, 0.2f, 1.0f }};
        clearValues[1].depthStencil = { 1.0f, 0 };

        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

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

        vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
        vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::end_render_pass() {
        vkCmdEndRenderPass(commandBuffer);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_pipeline(VulkanPipeline& pipeline) {
        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.graphicsPipeline);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_index_buffer(std::shared_ptr<VulkanBufferImpl>& indexBuffer) {
        // Todo, note that VK_INDEX_TYPE_UINT32 should match index size, akka for int should be used VK_INDEX_TYPE_UINT32
        vkCmdBindIndexBuffer(commandBuffer, indexBuffer->get_buffer(), 0, VK_INDEX_TYPE_UINT32);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::draw(const size_t& vertexCount) {
        vkCmdDraw(commandBuffer, vertexCount, 1, 0, 0);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::draw_indexed(const size_t& indexCount) {
        vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indexCount), 1, 0, 0, 0);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::bind_descriptor_set(std::shared_ptr<VulkanPipelineLayoutImpl>& pipelineLayout, VkDescriptorSet& descriptorSet) {
        vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout->get_layout(), 0, 1, &descriptorSet, 0, nullptr);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::push_constant(std::shared_ptr<VulkanPipelineLayoutImpl>& pipelineLayout, const uint32_t& size, const void* constantPtr) {
        vkCmdPushConstants(commandBuffer, pipelineLayout->get_layout(), VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, 0, size, constantPtr);

        return *this;
    }

    VulkanCommandBuffer& VulkanCommandBuffer::push_constant(std::shared_ptr<VulkanPipelineLayoutImpl>& pipelineLayout, const uint32_t& size, const size_t& offset, const void* constantPtr) {
        vkCmdPushConstants(commandBuffer, pipelineLayout->get_layout(), VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT, offset, size, constantPtr);

        return *this;
    }
}
