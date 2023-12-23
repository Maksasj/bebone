#ifndef DEVICE_H
#define DEVICE_H

#include "../gfx_backend.h"
#include "../window/window.h"

#include "vulkan_instance.h"
#include "vulkan_device_chooser.h"
#include "vulkan_buffer.h"

#include <iostream>
#include <set>
#include <unordered_set>

namespace bebone::gfx {
    class VulkanSwapChain;
    class VulkanPipeline;
    class ShaderCode;
    class VulkanDescriptorPool;
    class VulkanCommandBufferPool;
    class VulkanShaderModule;
    class VulkanPipelineLayout;
    class VulkanDescriptorSetLayout;
    class VulkanDescriptorSetLayoutBinding;

    struct ShaderType;

    class VulkanDevice : private core::NonCopyable {
        private:
            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

            VkDevice device_;
            VkSurfaceKHR surface_;

            VkQueue graphicsQueue_;
            VkQueue presentQueue_;

            VulkanInstance &vulkanInstance;

            void pickPhysicalDevice(VulkanInstance &vulkanInstance);
            void createLogicalDevice();

        public:
            VkPhysicalDeviceProperties properties;

            VulkanDevice(VulkanInstance& _vulkanInstance, VulkanWindow &window);
            ~VulkanDevice();

            std::shared_ptr<VulkanBuffer> create_buffer(const size_t& size);
            std::vector<std::shared_ptr<VulkanBuffer>> create_buffers(const size_t& size, const size_t& bufferCount);

            std::shared_ptr<VulkanDescriptorPool> create_descriptor_pool();
            std::vector<std::shared_ptr<VulkanDescriptorSetLayout>> create_descriptor_set_layouts(const std::vector<VulkanDescriptorSetLayoutBinding>& bindings);

            std::shared_ptr<VulkanPipelineLayout> create_pipeline_layout(
                    const std::vector<std::shared_ptr<VulkanDescriptorSetLayout>>& layouts,
                    const std::vector<VkPushConstantRange>& constantRanges);
            std::shared_ptr<VulkanPipeline> create_pipeline(
                std::shared_ptr<VulkanSwapChain>& swapChain,
                std::shared_ptr<VulkanPipelineLayout>& pipelineLayout,
                std::shared_ptr<VulkanShaderModule>& vertShaderModule,
                std::shared_ptr<VulkanShaderModule>& fragShaderModule);

            std::shared_ptr<VulkanCommandBufferPool> create_command_buffer_pool();
            std::shared_ptr<VulkanShaderModule> create_shader_module(const std::string& shaderCodePath, const ShaderType& type);
            std::shared_ptr<VulkanSwapChain> create_swap_chain(std::shared_ptr<Window>& window);

            void wait_idle() {
                vkDeviceWaitIdle(device_);
            }

            VkDevice device() const { return device_; }
            VkSurfaceKHR surface() { return surface_; }
            VkQueue graphicsQueue() { return graphicsQueue_; }
            VkQueue presentQueue() { return presentQueue_; }

            void createImageWithInfo(const VkImageCreateInfo &imageInfo, VkMemoryPropertyFlags properties, VkImage &image, VkDeviceMemory &imageMemory);

            uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

            QueueFamilyIndices findPhysicalQueueFamilies() { return VulkanDeviceChooser::find_queue_families(physicalDevice, surface_); }
            SwapChainSupportDetails getSwapChainSupport() { return VulkanDeviceChooser::query_swap_chain_support(physicalDevice, surface_); }

            VkFormat findSupportedFormat(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        };
}

#endif