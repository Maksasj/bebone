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

#include "vulkan_device.h"

#include "vulkan_frame.h"

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

            std::shared_ptr<VulkanInstance> vulkanInstance;
            std::shared_ptr<VulkanDevice> device; // ORDER MATTERS FOR DESTRUCTOR

            std::shared_ptr<VulkanSwapChain> swapChain; // ORDER MATTERS FOR df
            std::shared_ptr<VulkanCommandBufferPool> commandBuffers; // ORDER MATTERS FOR DESTRUCTOR

            // Linked list since we want to avoid reallocation's
            std::list<VulkanPipeline*> pipelines;

            // vulkanPipelineLayout should be saved somewhere
            VulkanPipelineLayoutImpl* vulkanPipelineLayout;

            VulkanRenderer(Window& window)
                : _window(window),
                  vulkanPipelineLayout(nullptr) {

                vulkanInstance = VulkanInstance::create_instance();

                device = vulkanInstance->create_device(_window);

                // Todo fif should be moved to swap chain, or no
                swapChain = device->create_swapchain(_window);

                // Todo swapChain->get_image_count() basically same thing as fif
                commandBuffers = std::make_shared<VulkanCommandBufferPool>(*device, swapChain->get_image_count());
            }

            ~VulkanRenderer() {
                for(auto& pipeline : pipelines)
                    delete pipeline;

                commandBuffers = nullptr;
                swapChain = nullptr;
                device = nullptr;
                vulkanInstance = nullptr;
            }

            Pipeline create_pipeline(PipelineLayout& pipelineLayout, const ShaderCode& vertexSpirvCode, const ShaderCode& fragmentSpirvCode) {
                vulkanPipelineLayout = static_cast<VulkanPipelineLayoutImpl*>(pipelineLayout.get_impl()); // vulkanPipelineLayout should be saved somewhere

                PipelineConfigInfo pipelineConfig;
                PipelineConfigInfo::defaultPipelineConfigInfo(pipelineConfig);
                
                pipelineConfig.renderPass = swapChain->renderTarget->renderPass.renderPass; // Setting up render pass
                pipelineConfig.pipelineLayout = vulkanPipelineLayout->get_layout();

                VulkanPipeline* pipeline = new VulkanPipeline(*device, vertexSpirvCode, fragmentSpirvCode, pipelineConfig);
                pipelines.push_back(pipeline);

                return Pipeline(&pipelines.back());
            }

            VulkanVertexBufferImpl* create_vertex_buffer_impl(const std::vector<Vertex>& vertices) {
                VulkanVertexBufferImpl* vertexBufferImpl = new VulkanVertexBufferImpl(vertices, *device);
                return vertexBufferImpl;
            }

            VulkanIndexBufferImpl* create_index_buffer_impl(const std::vector<int>& indices) {
                VulkanIndexBufferImpl* indexBufferImpl = new VulkanIndexBufferImpl(indices, *device);
                return indexBufferImpl;
            }

            PipelineLayoutBuilder create_pipeline_layout_builder() {
                return PipelineLayoutBuilder::create_from_impl<VulkanPipelineLayoutBuilderImpl>(*device);
            }

            VulkanSwapChain& get_swap_chain() {
                return *swapChain;
            }

            GPUResourceManager create_gpu_resource_manager() {
                return GPUResourceManager(swapChain->get_image_count(), *device);
            }

            void recreate_pipelines() const {
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
            }

            VulkanFrame get_frame() const {
                uint32_t imageIndex;
                auto result = swapChain->acquireNextImage(&imageIndex);

                if(result == VK_ERROR_OUT_OF_DATE_KHR) {
                    // This logic needs to be abstracted away
                    recreate_pipelines();
                    return VulkanFrame::invalid;
                }

                if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
                    throw std::runtime_error("failed to acquire swap chain image!");
                }

                return VulkanFrame(imageIndex, &commandBuffers->get_command_buffer(imageIndex));
            }

            void present(VulkanFrame& frame) {
                VkCommandBuffer& commnandBuffer = frame.get_command_buffer().commandBuffer;

                auto result = swapChain->submitCommandBuffers(&commnandBuffer, &frame.frameIndex);

                if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || _window.is_resized()) {
                    // This logic needs to be abstracted away
                    recreate_pipelines();
                    return;
                }

                if(result != VK_SUCCESS)
                    throw std::runtime_error("failed to acquire submit command buffers !\n");
            }
    };
}
#endif
