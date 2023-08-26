#ifndef _BEBONE_GFX_VULKAN_RENDERER_H_
#define _BEBONE_GFX_VULKAN_RENDERER_H_

#include <list>
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

#include "../render_target.h"

#include "../pipeline_layout_builder.h"

#include "../gpu_resource_manager.h"

#include "../window/window.h"

namespace bebone::gfx {
    class VulkanRenderer {
        public:
            Window& _window;

            const static constexpr size_t FIF = 2; 

            std::unique_ptr<DeviceImpl> device; // ORDER MATTERS FOR DESTRUCTOR
            std::unique_ptr<MyEngineSwapChainImpl> swapChain; // ORDER MATTERS FOR DESTRUCTOR
            std::unique_ptr<VulkanCommandBufferPool> commandBuffers; // ORDER MATTERS FOR DESTRUCTOR

            // Linked list since we want to avoid reallocations
            std::list<VulkanPipeline*> pipelines;

            // vulkanPipelineLayout should be saved somewhere
            VulkanPipelineLayoutImpl* vulkanPipelineLayout;

            VulkanRenderer(Window& window) : _window(window) {
                device = std::make_unique<DeviceImpl>(_window);
                swapChain = std::make_unique<MyEngineSwapChainImpl>(*device, _window.get_extend(), FIF);
                commandBuffers = std::make_unique<VulkanCommandBufferPool>(*device, FIF);
            }

            ~VulkanRenderer() {
                for(auto& pipeline : pipelines) {
                    delete pipeline;
                }
            }

            Pipeline create_pipeline(PipelineLayout& pipelineLayout, const std::vector<unsigned int>& vertexSpirvCode, const std::vector<unsigned int>& fragmentSpirvCode) {
                vulkanPipelineLayout = static_cast<VulkanPipelineLayoutImpl*>(pipelineLayout.get_impl()); // vulkanPipelineLayout should be saved somewhere

                PipelineConfigInfo pipelineConfig;
                PipelineConfigInfo::defaultPipelineConfigInfo(pipelineConfig);
                
                pipelineConfig.renderPass = swapChain->renderTarget->renderPass.renderPass; // Setting up render pass
                pipelineConfig.pipelineLayout = vulkanPipelineLayout->get_layout();

                VulkanPipeline* pipeline = new VulkanPipeline(*device, vertexSpirvCode, fragmentSpirvCode, pipelineConfig);
                pipelines.push_back(pipeline);

                return Pipeline(&pipelines.back());
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

            MyEngineSwapChainImpl& get_swap_chain() {
                return *swapChain;
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

                if(result == VK_ERROR_OUT_OF_DATE_KHR) {
                    // This logic needs to be abstracted away
                    vkDeviceWaitIdle(device->device());

                    swapChain->recreate(_window.get_extend());

                    for(auto& pipeline : pipelines) {
                        PipelineConfigInfo pipelineConfig;
                        PipelineConfigInfo::defaultPipelineConfigInfo(pipelineConfig);
                        
                        pipelineConfig.renderPass = swapChain->renderTarget->renderPass.renderPass; // Setting up render pass
                        pipelineConfig.pipelineLayout = vulkanPipelineLayout->get_layout(); // vulkanPipelineLayout should be saved somewhere

                        pipeline->recreate(pipelineConfig);
                    }

                    return 9999; 
                }

                if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
                    throw std::runtime_error("failed to acquire swap chain image!");
                }

                return imageIndex;
            }

            void present(uint32_t& imageIndex) {
                VkCommandBuffer& _commnandBuffer = static_cast<VulkanCommandBuffer&>(commandBuffers->get_command_buffer(imageIndex)).commandBuffer; 

                auto result = swapChain->submitCommandBuffers(&_commnandBuffer, &imageIndex);

                if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || _window.is_resized()) {
                    // This logic needs to be abstracted away
                    vkDeviceWaitIdle(device->device());

                    _window.reset_resize_flag();
                    swapChain->recreate(_window.get_extend());
                    
                    for(auto& pipeline : pipelines) {
                        PipelineConfigInfo pipelineConfig;
                        PipelineConfigInfo::defaultPipelineConfigInfo(pipelineConfig);
                        
                        pipelineConfig.renderPass = swapChain->renderTarget->renderPass.renderPass; // Setting up render pass
                        pipelineConfig.pipelineLayout = vulkanPipelineLayout->get_layout(); // vulkanPipelineLayout should be saved somewhere

                        pipeline->recreate(pipelineConfig);
                    }

                    return;
                }

                if(result != VK_SUCCESS) {
                    throw std::runtime_error("failed to acquire submit command buffers !\n");
                }
            }
    };
}
#endif
