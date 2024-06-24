#ifndef _BEBONE_GFX_VULKAN_VULKAN_DEVICE_H_
#define _BEBONE_GFX_VULKAN_VULKAN_DEVICE_H_

#include <iostream>
#include <set>
#include <unordered_set>

#include "../gfx_backend.h"
#include "../window/window.h"

#include "../shaders/shader_type.h"
#include "../shaders/shader_code.h"

#include "vulkan_wrapper.tpp"
#include "vulkan_instance.h"
#include "vulkan_device_chooser.h"

#include "vulkan_buffer.h"
#include "vulkan_image.h"
#include "vulkan_sampler.h"
#include "vulkan_image_view.h"
#include "vulkan_pipeline.h"
#include "vulkan_texture.h"
#include "vulkan_descriptor_set.h"
#include "vulkan_descriptor_set_layout_binding.h"

#include "vulkan_buffer_tuples.h"
#include "vulkan_image_tuples.h"

namespace bebone::gfx::vulkan {
    class VulkanSwapChain;
    class VulkanPipeline;
    class VulkanDescriptorPool;
    class VulkanCommandBufferPool;
    class VulkanShaderModule;
    class VulkanPipelineLayout;
    class VulkanDescriptorSetLayout;
    class VulkanConstRange;
    class VulkanPipelineManager;

    class VulkanDevice : private core::NonCopyable {
        private:
            VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

            VkDevice device_;
            VkSurfaceKHR surface_;

            VkQueue graphicsQueue_;
            VkQueue presentQueue_;

            VulkanInstance &vulkanInstance;

            void pick_physical_device(VulkanInstance &vulkanInstance);
            void create_logical_device();

        public:
            VkPhysicalDeviceProperties properties;

            VulkanDevice(
                VulkanInstance& _vulkanInstance,
                VulkanWindow &window);

            std::shared_ptr<VulkanDeviceMemory> create_device_memory(
                VkMemoryRequirements memRequirements,
                VkMemoryPropertyFlags properties);

            std::shared_ptr<VulkanBuffer> create_buffer(
                const size_t& size,
                VulkanBufferInfo bufferInfo = {});

            VulkanBufferMemoryTuple create_buffer_memory(
                const size_t& size,
                VulkanBufferInfo bufferInfo = {});

            template<typename T>
            VulkanBufferMemoryTuple create_buffer_memory_from(const std::vector<T>& data, VulkanBufferInfo bufferInfo = {}) {
                const auto size = sizeof(T) * data.size();
                VulkanBufferMemoryTuple tuple = create_buffer_memory(size, bufferInfo);
                auto [ _, bmemory ] = tuple;

                bmemory->upload_data(*this, data.data(), size);

                return tuple;
            }

            std::vector<std::shared_ptr<VulkanBuffer>> create_buffers(
                const size_t& size,
                const size_t& bufferCount,
                VulkanBufferInfo bufferInfo = {});

            std::vector<VulkanBufferMemoryTuple> create_buffer_memorys(
                const size_t& size,
                const size_t& bufferCount,
                VulkanBufferInfo bufferInfo = {});

            std::shared_ptr<VulkanImage> create_image(
                VkFormat format,
                VkExtent3D extent,
                VulkanImageInfo imageInfo = {});

            VulkanImageMemoryTuple create_image_memory(VkFormat format, VkExtent3D extent, VulkanImageInfo imageInfo);

            std::shared_ptr<VulkanImage> create_image(
                VkImage& image);

            std::shared_ptr<VulkanSampler> create_sampler();

            std::shared_ptr<VulkanImageView> create_image_view(
                VulkanImage& image,
                const VkFormat& imageFormat,
                VulkanImageViewInfo imageViewInfo = {});

            std::shared_ptr<VulkanDescriptorPool> create_descriptor_pool();

            std::shared_ptr<VulkanDescriptorSetLayout> create_descriptor_set_layout(
                const std::vector<VulkanDescriptorSetLayoutBinding>& bindings);

            std::vector<std::shared_ptr<VulkanDescriptorSetLayout>> create_descriptor_set_layouts(
                const std::vector<VulkanDescriptorSetLayoutBinding>& bindings);

            void update_descriptor_set(
                const std::shared_ptr<VulkanBuffer>& buffer,
                std::shared_ptr<VulkanDescriptorSet>& descriptorSet,
                const size_t& binding,
                const size_t& dstArrayElement
            );

            void update_descriptor_set(
                const std::shared_ptr<VulkanTexture>& texture,
                std::shared_ptr<VulkanDescriptorSet>& descriptorSet,
                const size_t& binding,
                const size_t& dstArrayElement
            );

            void update_descriptor_set(
                const std::shared_ptr<VulkanSampler>& sampler,
                const std::shared_ptr<VulkanImageView>& view,
                const std::shared_ptr<VulkanDescriptorSet>& descriptorSet,
                const size_t& binding,
                const size_t& dstArrayElement
            );

            void update_descriptor_set(
                VulkanBufferMemoryTuple& tuple,
                std::shared_ptr<VulkanDescriptorSet>& descriptorSet,
                const size_t& binding,
                const size_t& dstArrayElement
            );

            void update_descriptor_sets(
                std::vector<std::shared_ptr<VulkanBuffer>>& buffers,
                std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptorSets,
                const size_t& binding,
                const std::vector<size_t>& dstArrayElements
            );

            void update_descriptor_sets(
                const std::vector<VulkanBufferMemoryTuple>& tuples,
                std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptorSets,
                const size_t& binding,
                const std::vector<size_t>& dstArrayElements
            );

            void update_descriptor_sets(
                std::shared_ptr<VulkanTexture>& texture,
                std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptorSets,
                const size_t& binding,
                const std::vector<size_t>& dstArrayElements
            );

            std::shared_ptr<VulkanPipelineLayout> create_pipeline_layout(
                const std::vector<std::shared_ptr<VulkanDescriptorSetLayout>>& layouts,
                const std::vector<VulkanConstRange>& constantRanges);

            std::shared_ptr<VulkanPipeline> create_pipeline(
                std::shared_ptr<VulkanSwapChain>& swapChain,
                std::shared_ptr<VulkanPipelineLayout>& pipelineLayout,
                std::vector<std::shared_ptr<VulkanShaderModule>> shaderModules,
                VulkanPipelineConfig configInfo = {});

            std::shared_ptr<VulkanCommandBufferPool> create_command_buffer_pool();

            std::shared_ptr<VulkanShaderModule> create_shader_module(
                const std::string& shaderCodePath,
                const ShaderType& type);

            std::shared_ptr<VulkanTexture> create_texture(
                std::shared_ptr<VulkanCommandBufferPool>& commandBufferPool,
                const std::string& filePath);

            std::shared_ptr<VulkanPipelineManager> create_pipeline_manager();

            std::shared_ptr<VulkanSwapChain> create_swap_chain(std::shared_ptr<Window>& window);

            void wait_idle();

            VkDevice device() { return device_; }
            VkSurfaceKHR surface() { return surface_; }
            VkQueue graphicsQueue() { return graphicsQueue_; }
            VkQueue presentQueue() { return presentQueue_; }

            uint32_t find_memory_type(uint32_t typeFilter, VkMemoryPropertyFlags properties);

            QueueFamilyIndices find_physical_queue_families() { return VulkanDeviceChooser::find_queue_families(physicalDevice, surface_); }
            SwapChainSupportDetails get_swap_chain_support() { return VulkanDeviceChooser::query_swap_chain_support(physicalDevice, surface_); }

            VkFormat find_supported_format(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

            template <typename... Args>
            void destroy_all(Args... args) {
                (args.destroy(*this), ...);
            }

            template <typename... Args>
            void destroy_all(std::shared_ptr<Args>... args) {
                (args->destroy(*this), ...);
            }

            template <typename... Args>
            void destroy_all(std::vector<std::shared_ptr<Args>>... args) {
                for(auto& arg : (args, ...)) {
                    arg->destroy(*this);
                }
            }

            void destroy();

            VkFormat find_depth_format();
    };
}

#endif