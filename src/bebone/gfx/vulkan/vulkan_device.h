#ifndef _BEBONE_GFX_VULKAN_DEVICE_H_
#define _BEBONE_GFX_VULKAN_DEVICE_H_

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
#include "vulkan_texture_tuple.h"
#include "vulkan_descriptor_set.h"
#include "vulkan_descriptor_set_layout_binding.h"
#include "vulkan_attachment.h"

#include "vulkan_buffer_tuples.h"
#include "vulkan_image_tuples.h"

namespace bebone::gfx {
    class VulkanSwapChain;
    class VulkanPipeline;
    class VulkanDescriptorPool;
    class VulkanCommandBufferPool;
    class VulkanCommandBuffer;
    class VulkanShaderModule;
    class VulkanPipelineLayout;
    class VulkanDescriptorSetLayout;
    class VulkanConstRange;
    class VulkanPipelineManager;
    class VulkanRenderTarget;
    class VulkanRenderPass;
    class VulkanFramebuffer;

    class VulkanDevice : private core::NonCopyable {
        private:
            VulkanInstance& instance_owner;

            // Todo, abstract all things below
            VkPhysicalDevice physical_device = VK_NULL_HANDLE;

            void pick_physical_device(VulkanInstance &instance);
            void create_logical_device();

            // Todo, maybe this can be optimized
            std::unique_ptr<VulkanCommandBufferPool> command_buffer_pool;

        public:
            VkDevice device;
            VkSurfaceKHR surface;
            VkQueue graphics_queue;
            VkQueue present_queue;

            VkPhysicalDeviceProperties properties;

            VulkanDevice(VulkanInstance& instance, std::unique_ptr<Window>& window);
            ~VulkanDevice();

            std::unique_ptr<VulkanDeviceMemory> create_device_memory(
                VkMemoryRequirements requirements,
                VkMemoryPropertyFlags properties);

            std::unique_ptr<VulkanBufferMemoryTuple> create_buffer_memory(
                const size_t& size,
                VulkanBufferInfo buffer_info = {});

            template<typename T>
            std::unique_ptr<VulkanBufferMemoryTuple> create_buffer_memory_from(
                const std::vector<T>& data,
                VulkanBufferInfo buffer_info = {}
            ) {
                const auto size = sizeof(T) * data.size();
                auto tuple = create_buffer_memory(size, buffer_info);
                auto [ _, b_memory ] = tuple;

                b_memory->upload_data(data.data(), size);

                return tuple;
            }

            std::vector<std::unique_ptr<VulkanBuffer>> create_buffers(
                const size_t& size,
                const size_t& count,
                VulkanBufferInfo buffer_info = {});

            std::vector<std::unique_ptr<VulkanBufferMemoryTuple>> create_buffer_memorys(
                const size_t& size,
                const size_t& count,
                VulkanBufferInfo buffer_info = {});

            std::unique_ptr<VulkanImage> create_image(
                VkFormat format,
                VkExtent3D extent,
                VulkanImageInfo image_info = {});

            // Todo
            std::unique_ptr<VulkanImageMemoryTuple> create_image_memory(
                VkFormat format,
                VkExtent3D extent,
                VulkanImageInfo image_info);

            std::unique_ptr<VulkanImage> create_image(VkImage& image);

            std::unique_ptr<VulkanSampler> create_sampler();

            std::unique_ptr<VulkanImageView> create_image_view(
                VulkanImage& image,
                const VkFormat& image_format,
                VulkanImageViewInfo image_view_info = {});

            std::unique_ptr<VulkanDepthImageTuple> create_depth_image_tuple(VkExtent3D extent);
            std::vector<std::unique_ptr<VulkanDepthImageTuple>> create_depth_image_tuples(VkExtent3D extent, const size_t& count);

            std::unique_ptr<VulkanDescriptorPool> create_descriptor_pool();

            std::unique_ptr<VulkanDescriptorSetLayout> create_descriptor_set_layout(
                const std::vector<VulkanDescriptorSetLayoutBinding>& bindings);

            std::vector<std::unique_ptr<VulkanDescriptorSetLayout>> create_descriptor_set_layouts(
                const std::vector<VulkanDescriptorSetLayoutBinding>& bindings);

            // Update descriptor set for single
            void update_descriptor_set(
                const std::unique_ptr<VulkanBuffer>& buffer,
                std::unique_ptr<VulkanDescriptorSet>& descriptor_set,
                const size_t& binding,
                const size_t& dst_array_element);

            void update_descriptor_set(
                const std::unique_ptr<VulkanSampler>& sampler,
                const std::unique_ptr<VulkanImageView>& view,
                std::unique_ptr<VulkanDescriptorSet>& descriptor_set,
                const size_t& binding,
                const size_t& dst_array_element);

            // Update descriptor sets for multiple descriptors
            void update_descriptor_sets(
                const std::vector<std::unique_ptr<VulkanBuffer>>& buffers,
                std::vector<std::unique_ptr<VulkanDescriptorSet>>& descriptor_sets,
                const size_t& binding,
                const std::vector<size_t>& dst_array_elements);

            void update_descriptor_sets(
                const std::vector<std::unique_ptr<VulkanBufferMemoryTuple>>& tuples,
                std::vector<std::unique_ptr<VulkanDescriptorSet>>& descriptor_sets,
                const size_t& binding,
                const std::vector<size_t>& dst_array_elements);

            void update_descriptor_sets(
                const std::unique_ptr<VulkanSampler>& sampler,
                const std::unique_ptr<VulkanImageView>& view,
                std::vector<std::unique_ptr<VulkanDescriptorSet>>& descriptor_sets,
                const size_t& binding,
                const std::vector<size_t>& dst_array_elements);

            // Other
            std::unique_ptr<VulkanPipelineLayout> create_pipeline_layout(
                const std::vector<std::unique_ptr<VulkanDescriptorSetLayout>>& layouts,
                const std::vector<VulkanConstRange>& constant_ranges);

            std::unique_ptr<VulkanPipeline> create_pipeline(
                const std::unique_ptr<VulkanRenderPass>& render_pass,
                VulkanPipelineLayout& pipeline_layout,
                const std::vector<std::unique_ptr<VulkanShaderModule>>& shader_modules,
                VulkanPipelineConfig config_info = {});

            std::unique_ptr<VulkanPipeline> create_pipeline(
                const std::unique_ptr<VulkanRenderPass>& render_pass,
                VulkanPipelineLayout& pipeline_layout,
                const std::string& vertex_shader_path,
                const std::string& fragment_shader_path,
                VulkanPipelineConfig config_info = {});

            std::unique_ptr<VulkanRenderPass> create_render_pass(VkExtent2D extent, const std::vector<VulkanAttachmentDesc>& attachments);

            std::unique_ptr<VulkanFramebuffer> create_framebuffer(
                    const std::vector<std::unique_ptr<VulkanImageView>>& attachments,
                    const std::unique_ptr<VulkanRenderPass>& render_pass,
                    VkExtent2D extent);

            std::vector<std::unique_ptr<VulkanFramebuffer>> create_framebuffers(
                    const std::vector<std::unique_ptr<VulkanImageView>>& attachments,
                    const std::unique_ptr<VulkanRenderPass>& render_pass,
                    VkExtent2D extent,
                    const size_t& count);

            // Create new instance of command buffer pool
            std::unique_ptr<VulkanCommandBufferPool> create_command_buffer_pool();

            // Create command buffer from personal command buffer pool
            std::unique_ptr<VulkanCommandBuffer> create_command_buffer();

            // Create command buffers from personal command buffer pool
            std::vector<std::unique_ptr<VulkanCommandBuffer>> create_command_buffers(const size_t& count);

            std::unique_ptr<VulkanCommandBuffer> begin_single_time_commands();
            void end_single_time_commands(std::unique_ptr<VulkanCommandBuffer>& command_buffer);

            std::unique_ptr<VulkanShaderModule> create_shader_module(
                const std::string& source_code,
                const ShaderType& type);

            std::unique_ptr<VulkanTextureTuple> create_texture(
                const std::string& file_path);

            std::unique_ptr<VulkanTextureTuple> create_texture(
                VkExtent3D extent,
                VkFormat image_format);

            std::vector<std::unique_ptr<VulkanTextureTuple>> create_textures(
                VkExtent3D extent,
                VkFormat image_format,
                const size_t& count);

            std::unique_ptr<VulkanPipelineManager> create_pipeline_manager();

            std::unique_ptr<VulkanRenderTarget> create_render_target(
                std::unique_ptr<VulkanRenderPass>& render_pass);

            // Special constructor for swap chain
            std::unique_ptr<VulkanRenderTarget> create_render_target(
                std::unique_ptr<VulkanRenderPass>& render_pass,
                std::vector<std::unique_ptr<VulkanSwapChainImageTuple>>& images);

            std::unique_ptr<VulkanSwapChain> create_swap_chain(std::unique_ptr<Window>& window);

            void wait_idle();

            uint32_t find_memory_type(uint32_t type_filter, VkMemoryPropertyFlags properties);

            VulkanQueueFamilyIndices find_physical_queue_families() { return VulkanDeviceChooser::find_queue_families(physical_device, surface); }
            VulkanSwapChainSupportDetails get_swap_chain_support() { return VulkanDeviceChooser::query_swap_chain_support(physical_device, surface); }

            VkFormat find_supported_format(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

            /*
            template <typename... Args>
            void destroy_all(Args... args) {
                (args.destroy(*this), ...);
            }

            template <typename... Args>
            void destroy_all(std::unique_ptr<Args>... args) {
                (args->destroy(*this), ...);
            }

            template <typename... Args>
            void destroy_all(std::vector<std::unique_ptr<Args>>... args) {
                for(auto& arg : (args, ...)) {
                    arg->destroy(*this);
                }
            }

            void collect_garbage();

            void destroy(VulkanInstance& instance);
            */

            VkFormat find_depth_format();
    };
}

#endif