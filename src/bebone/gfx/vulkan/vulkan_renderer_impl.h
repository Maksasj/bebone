#ifndef _BEBONE_GFX_VULKAN_RENDERER_H_
#define _BEBONE_GFX_VULKAN_RENDERER_H_

#include <memory>

#include "../gfx_backend.h"

#include "vulkan_command_buffer_pool.h"
#include "vulkan_command_buffer.h"

#include "vulkan_vertex_buffer_impl.h"
#include "vulkan_index_buffer_impl.h"

#include "vulkan_pipeline_impl.h"

#include "../vertex_buffer.h"
#include "../pipeline.h"

#include "../device_impl.h"

#include "../vulkan_uniform_buffer_impl.h"
#include "vulkan_descriptor_pool.h"
#include "vulkan_pipeline_layout_impl.h"
#include "vulkan_pipeline_layout_builder_impl.h"

#include "../pipeline_layout_builder.h"

#include "../gpu_resource_manager.h"

namespace bebone::gfx {
    class VulkanRenderer {
        public:
            const static constexpr size_t FIF = 2; 

            std::shared_ptr<VulkanCommandBufferPool> commandBuffers;
            std::shared_ptr<DeviceImpl> device;
            std::shared_ptr<MyEngineSwapChainImpl> swapChain;

            VulkanRenderer(Window& window) {
                device = std::make_shared<DeviceImpl>(window);
                swapChain = std::make_shared<MyEngineSwapChainImpl>(*device, window.get_extend(), FIF);
                commandBuffers = std::make_shared<VulkanCommandBufferPool>(*device, FIF);
            }

            ~VulkanRenderer() {
                // vkDeviceWaitIdle(device.device());
                // vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
                // vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
            }

            VulkanPipeline create_pipeline(PipelineLayout& pipelineLayout, const std::vector<unsigned int>& vertexSpirvCode, const std::vector<unsigned int>& fragmentSpirvCode) {
                VulkanPipelineLayoutImpl* vulkanPipelineLayout = static_cast<VulkanPipelineLayoutImpl*>(pipelineLayout.get_impl());

                auto pipelineConfig = VulkanPipeline::defaultPipelineConfigInfo(swapChain->width(), swapChain->height());
                pipelineConfig.renderPass = swapChain->getRenderPass(); // Setting up render pass
                pipelineConfig.pipelineLayout = vulkanPipelineLayout->get_layout();

                return VulkanPipeline(*device, vertexSpirvCode, fragmentSpirvCode, pipelineConfig);
            }
            
            VertexBuffer create_vertex_buffer(const std::vector<Vertex>& vertices) {
                return VertexBuffer::create_from_impl<VulkanVertexBufferImpl>(vertices, *device);
            }

            IndexBuffer create_index_buffer(const std::vector<int>& indices) {
                return IndexBuffer::create_from_impl<VulkanIndexBufferImpl>(indices, *device);
            }

            PipelineLayoutBuilder create_pipeline_layout_builder() {
                return PipelineLayoutBuilder::create_from_impl<VulkanPipelineLayoutBuilderImpl>(*device);
            }

            std::shared_ptr<MyEngineSwapChainImpl> get_swap_chain() {
                return swapChain;
            }

            VulkanCommandBuffer& get_command_buffer() {
                return commandBuffers->get_command_buffer(1);
            }

            VulkanCommandBufferPool& get_command_buffer_pool() {
                return *commandBuffers;
            }

            GPUResourceManager create_gpu_resource_manager() {
                return GPUResourceManager(FIF, *device);
            }

            uint32_t get_frame() const {
                uint32_t imageIndex;
                auto result = swapChain->acquireNextImage(&imageIndex);

                if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
                    throw std::runtime_error("failed to acquire swap chain image!");
                }

                return imageIndex;
            }

            void present(uint32_t& imageIndex) {
                VkCommandBuffer& _commnandBuffer = static_cast<VulkanCommandBuffer&>(commandBuffers->get_command_buffer(imageIndex)).commandBuffer; 

                auto result = swapChain->submitCommandBuffers(&_commnandBuffer, &imageIndex);
                if(result != VK_SUCCESS) {
                    throw std::runtime_error("failed to acquire submit command buffers !\n");
                }
            }
    };
}
#endif
