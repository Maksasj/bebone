#ifndef _BEBONE_GFX_VULKAN_RENDERER_H_
#define _BEBONE_GFX_VULKAN_RENDERER_H_

#include <memory>

#include "../gfx_backend.h"
#include "../renderer.h"

#include "vulkan_command_buffer_pool.h"
#include "vulkan_command_buffer.h"
#include "vulkan_vertex_buffer.h"

#include "../device.h"

namespace bebone::gfx {
    class VulkanRenderer : public Renderer {
        private:
            std::shared_ptr<VulkanCommandBufferPool> commandBuffers;
            std::shared_ptr<MyEngineDevice> device;
            std::shared_ptr<MyEngineSwapChain> swapChain;

        public:
            VulkanRenderer(Window& window) {
                device = std::make_shared<MyEngineDevice>(window);
                swapChain = std::make_shared<MyEngineSwapChain>(*device, window.get_extend());
                commandBuffers = std::make_shared<VulkanCommandBufferPool>(*device, 2);
            }

            ~VulkanRenderer() {
                // vkDeviceWaitIdle(device.device());
                // vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
            }

            std::shared_ptr<Pipeline> create_pipeline(const std::vector<unsigned int>& vertexSpirvCode, const std::vector<unsigned int>& fragmentSpirvCode) override {
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

                auto pipelineConfig = Pipeline::defaultPipelineConfigInfo(swapChain->width(), swapChain->height());
                pipelineConfig.renderPass = swapChain->getRenderPass();
                pipelineConfig.pipelineLayout = pipelineLayout;

                return std::make_shared<Pipeline>(*device, vertexSpirvCode, fragmentSpirvCode, pipelineConfig);
            }

            std::shared_ptr<VertexBuffer> create_vertex_buffer(const std::vector<Vertex>& vertices) override {
                return std::make_shared<VulkanVertexBuffer>(vertices, *device);
            }

            std::shared_ptr<MyEngineSwapChain> get_swap_chain() override {
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
