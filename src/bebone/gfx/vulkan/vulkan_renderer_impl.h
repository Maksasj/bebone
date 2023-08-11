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


#include "vulkan_uniform_buffer_pool.h"
#include "vulkan_descriptor_pool.h"
#include "vulkan_pipeline_layout.h"

namespace bebone::gfx {
    class VulkanRendererImpl : public RendererImpl {
        private:
            std::shared_ptr<VulkanCommandBufferPool> commandBuffers;
            std::shared_ptr<VulkanUniformBufferPool> uniformBuffers;

            std::shared_ptr<VulkanDescriptorPool> descriptorPool;

            std::shared_ptr<DeviceImpl> device;
            std::shared_ptr<MyEngineSwapChainImpl> swapChain;

            std::shared_ptr<VulkanPipelineLayout> pipelineLayout;

        public:
            VulkanRendererImpl(Window& window) {
                device = std::make_shared<DeviceImpl>(window);
                swapChain = std::make_shared<MyEngineSwapChainImpl>(*device, window.get_extend());
                commandBuffers = std::make_shared<VulkanCommandBufferPool>(*device, 2);
                uniformBuffers = std::make_shared<VulkanUniformBufferPool>(sizeof(float), 2,*device);
            
                /**
                 * Todo
                 * Theoretically set layours and all 
                 * these constants things should be 
                 * computed from shader code, as well 
                 * as automatically should be created 
                 * all descriptiors like ubo's, etc
                */
                VkDescriptorSetLayout descriptorSetLayout;

                VkDescriptorSetLayoutBinding uboLayoutBinding{};
                uboLayoutBinding.binding = 0;
                uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                uboLayoutBinding.descriptorCount = 1;
                uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
                uboLayoutBinding.pImmutableSamplers = nullptr; // Optional

                // Descriptor set
                VkDescriptorSetLayoutCreateInfo layoutInfo{};
                layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
                layoutInfo.bindingCount = 1;
                layoutInfo.pBindings = &uboLayoutBinding;

                if (vkCreateDescriptorSetLayout(device->device(), &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create descriptor set layout!");
                }


                pipelineLayout = std::make_shared<VulkanPipelineLayout>(descriptorSetLayout, *device);

                descriptorPool = std::make_shared<VulkanDescriptorPool>(descriptorSetLayout, *device, 2, *uniformBuffers);
            }

            ~VulkanRendererImpl() {
                // vkDeviceWaitIdle(device.device());
                // vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
                // vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
            }

            Pipeline create_pipeline(const std::vector<unsigned int>& vertexSpirvCode, const std::vector<unsigned int>& fragmentSpirvCode) override {
                /**
                 * Todo
                 * Theoretically set layours and all 
                 * these constants things should be 
                 * computed from shader code, as well 
                 * as automatically should be created 
                 * all descriptiors like ubo's, etc
                */

                // pipelineLayout = std::make_shared<VkPipelineLayout>();

                auto pipelineConfig = VulkanPipelineImpl::defaultPipelineConfigInfo(swapChain->width(), swapChain->height());
                pipelineConfig.renderPass = swapChain->getRenderPass();
                pipelineConfig.pipelineLayout = pipelineLayout->get_layout();

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

            VulkanDescriptorPool& get_descriptor_pool() override {
                return *descriptorPool;
            }

            PipelineLayout& get_pipeline_layout() override {
                return *pipelineLayout;
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
