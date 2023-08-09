#ifndef _BEBONE_GFX_VULKAN_RENDERER_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_RENDERER_IMPLEMENTATION_H_

#include <memory>

#include "../gfx_backend.h"
#include "../renderer_impl.h"

#include "vulkan_command_buffer_pool.h"
#include "vulkan_command_buffer.h"

#include "vulkan_vertex_buffer_impl.h"
#include "vulkan_index_buffer_impl.h"

#include "vulkan_pipeline_impl.h"

#include "../vertex_buffer.h"
#include "../pipeline.h"

#include "../device_impl.h"

namespace bebone::gfx {
    class VulkanRendererImpl : public RendererImpl {
        private:
            std::shared_ptr<VulkanCommandBufferPool> commandBuffers;
            std::shared_ptr<DeviceImpl> device;
            std::shared_ptr<MyEngineSwapChainImpl> swapChain;

        public:
            VulkanRendererImpl(Window& window) {
                device = std::make_shared<DeviceImpl>(window);
                swapChain = std::make_shared<MyEngineSwapChainImpl>(*device, window.get_extend());
                commandBuffers = std::make_shared<VulkanCommandBufferPool>(*device, 2);
            }

            ~VulkanRendererImpl() {
                // vkDeviceWaitIdle(device.device());
                // vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
            }

            Pipeline create_pipeline(const std::vector<unsigned int>& vertexSpirvCode, const std::vector<unsigned int>& fragmentSpirvCode) override {
                VkPipelineLayout pipelineLayout;

                VkPipelineLayoutCreateInfo pipelineLayouInfo{};
                pipelineLayouInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
                pipelineLayouInfo.setLayoutCount = 0;
                pipelineLayouInfo.pSetLayouts = nullptr;
                pipelineLayouInfo.pushConstantRangeCount = 0;
                pipelineLayouInfo.pPushConstantRanges = nullptr;

                if(vkCreatePipelineLayout(device->device(), &pipelineLayouInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
                    throw std::runtime_error("Failed to create pipeline layout");
                }

                auto pipelineConfig = VulkanPipelineImpl::defaultPipelineConfigInfo(swapChain->width(), swapChain->height());
                pipelineConfig.renderPass = swapChain->getRenderPass();
                pipelineConfig.pipelineLayout = pipelineLayout;

                return Pipeline::create_from_impl<VulkanPipelineImpl>(*device, vertexSpirvCode, fragmentSpirvCode, pipelineConfig);
            }

            VertexBuffer create_vertex_buffer(const std::vector<Vertex>& vertices) override {
                return VertexBuffer::create_from_impl<VulkanVertexBufferImpl>(vertices, *device);
            }

            IndexBuffer create_index_buffer(const std::vector<int>& indices) override {
                return IndexBuffer::create_from_impl<VulkanIndexBufferImpl>(indices, *device);
            }

            std::shared_ptr<MyEngineSwapChainImpl> get_swap_chain() override {
                return swapChain;
            }

            CommandBuffer& get_command_buffer() override {
                return commandBuffers->get_command_buffer(1);
            }

            CommandBufferPool& get_command_buffer_pool() override {
                return *commandBuffers;
            }

            void present() override {
                uint32_t imageIndex;
                auto result = swapChain->acquireNextImage(&imageIndex);

                if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
                    throw std::runtime_error("failed to acquire swap chain image!");
                }


                VkCommandBuffer& _commnandBuffer = static_cast<VulkanCommandBuffer&>(commandBuffers->get_command_buffer(imageIndex)).commandBuffer; 

                result = swapChain->submitCommandBuffers(&_commnandBuffer, &imageIndex);
                if(result != VK_SUCCESS) {
                    throw std::runtime_error("failed to acquire submit command buffers !\n");
                }
            }
    };
}
#endif
