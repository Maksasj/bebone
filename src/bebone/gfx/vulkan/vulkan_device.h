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
#include "vulkan_texture.h"
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
    class VulkanShaderModule;
    class VulkanPipelineLayout;
    class VulkanDescriptorSetLayout;
    class VulkanConstRange;
    class VulkanPipelineManager;
    class VulkanSwapChainRenderTarget;
    class VulkanRenderPass;
    class VulkanFramebuffer;

    class VulkanDevice : private core::NonCopyable {
        private:
            // Todo, abstract all things below
            VkPhysicalDevice physical_device = VK_NULL_HANDLE;

            void pick_physical_device(VulkanInstance &instance);
            void create_logical_device();

            // Todo, maybe this can be optimized
            std::vector<shared_ptr<VulkanApi>> child_objects;

        public:
            VkDevice device;
            VkSurfaceKHR surface;
            VkQueue graphics_queue;
            VkQueue present_queue;

            VkPhysicalDeviceProperties properties;

            VulkanDevice(
                VulkanInstance& instance,
                VulkanWindow &window);

            std::shared_ptr<VulkanDeviceMemory> create_device_memory(
                VkMemoryRequirements requirements,
                VkMemoryPropertyFlags properties);

            std::shared_ptr<VulkanBuffer> create_buffer(
                const size_t& size,
                VulkanBufferInfo buffer_info = {});

            VulkanBufferMemoryTuple create_buffer_memory(
                const size_t& size,
                VulkanBufferInfo buffer_info = {});

            template<typename T>
            VulkanBufferMemoryTuple create_buffer_memory_from(
                const std::vector<T>& data,
                VulkanBufferInfo buffer_info = {}
            ) {
                const auto size = sizeof(T) * data.size();
                auto tuple = create_buffer_memory(size, buffer_info);
                auto [ _, b_memory ] = tuple;

                b_memory->upload_data(*this, data.data(), size);

                return tuple;
            }

            std::vector<std::shared_ptr<VulkanBuffer>> create_buffers(
                const size_t& size,
                const size_t& count,
                VulkanBufferInfo buffer_info = {});

            std::vector<VulkanBufferMemoryTuple> create_buffer_memorys(
                const size_t& size,
                const size_t& count,
                VulkanBufferInfo buffer_info = {});

            std::shared_ptr<VulkanImage> create_image(
                VkFormat format,
                VkExtent3D extent,
                VulkanImageInfo image_info = {});

            // Todo
            VulkanImageMemoryTuple create_image_memory(
                VkFormat format,
                VkExtent3D extent,
                VulkanImageInfo image_info);

            std::shared_ptr<VulkanImage> create_image(VkImage& image);

            std::shared_ptr<VulkanSampler> create_sampler();

            std::shared_ptr<VulkanImageView> create_image_view(
                VulkanImage& image,
                const VkFormat& image_format,
                VulkanImageViewInfo image_view_info = {});

            std::shared_ptr<VulkanDescriptorPool> create_descriptor_pool();

            std::shared_ptr<VulkanDescriptorSetLayout> create_descriptor_set_layout(
                const std::vector<VulkanDescriptorSetLayoutBinding>& bindings);

            std::vector<std::shared_ptr<VulkanDescriptorSetLayout>> create_descriptor_set_layouts(
                const std::vector<VulkanDescriptorSetLayoutBinding>& bindings);

            void update_descriptor_set(
                const std::shared_ptr<VulkanBuffer>& buffer,
                std::shared_ptr<VulkanDescriptorSet>& descriptor_set,
                const size_t& binding,
                const size_t& dst_array_element
            );

            void update_descriptor_set(
                const std::shared_ptr<VulkanTexture>& texture,
                std::shared_ptr<VulkanDescriptorSet>& descriptor_set,
                const size_t& binding,
                const size_t& dst_array_element
            );

            void update_descriptor_set(
                const std::shared_ptr<VulkanSampler>& sampler,
                const std::shared_ptr<VulkanImageView>& view,
                std::shared_ptr<VulkanDescriptorSet>& descriptor_set,
                const size_t& binding,
                const size_t& dst_array_element);

            void update_descriptor_set(
                const VulkanBufferMemoryTuple& tuple,
                std::shared_ptr<VulkanDescriptorSet>& descriptor_set,
                const size_t& binding,
                const size_t& dst_array_element);

            void update_descriptor_sets(
                const std::vector<std::shared_ptr<VulkanBuffer>>& buffers,
                std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptor_sets,
                const size_t& binding,
                const std::vector<size_t>& dst_array_elements);

            void update_descriptor_sets(
                const std::vector<VulkanBufferMemoryTuple>& tuples,
                std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptor_sets,
                const size_t& binding,
                const std::vector<size_t>& dst_array_elements);

            void update_descriptor_sets(
                const std::shared_ptr<VulkanTexture>& texture,
                std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptor_sets,
                const size_t& binding,
                const std::vector<size_t>& dst_array_elements);

            std::shared_ptr<VulkanPipelineLayout> create_pipeline_layout(
                const std::vector<std::shared_ptr<VulkanDescriptorSetLayout>>& layouts,
                const std::vector<VulkanConstRange>& constant_ranges);

            std::shared_ptr<VulkanPipeline> create_pipeline(
                const std::shared_ptr<VulkanRenderPass>& render_pass,
                const std::shared_ptr<VulkanPipelineLayout>& pipeline_layout,
                const std::vector<std::shared_ptr<VulkanShaderModule>>& shader_modules,
                VulkanPipelineConfig config_info = {});

            std::shared_ptr<VulkanRenderPass> create_render_pass(const std::vector<VulkanAttachment>& attachments);

            std::shared_ptr<VulkanFramebuffer> create_framebuffer(
                    const std::vector<std::shared_ptr<VulkanImageView>>& attachments,
                    std::shared_ptr<VulkanRenderPass>& render_pass,
                    VkExtent2D extent);

            std::vector<std::shared_ptr<VulkanFramebuffer>> create_framebuffers(
                    const std::vector<std::shared_ptr<VulkanImageView>>& attachments,
                    std::shared_ptr<VulkanRenderPass>& render_pass,
                    VkExtent2D extent,
                    const size_t& count);

            std::shared_ptr<VulkanCommandBufferPool> create_command_buffer_pool();

            std::shared_ptr<VulkanShaderModule> create_shader_module(
                const std::string& file_path,
                const ShaderType& type);

            std::shared_ptr<VulkanTexture> create_texture(
                std::shared_ptr<VulkanCommandBufferPool>& command_buffer_pool, // Todo, Do not really like that command_buffer_pool is there
                const std::string& file_path);

            std::shared_ptr<VulkanTexture> create_texture(
                std::shared_ptr<VulkanCommandBufferPool>& command_buffer_pool, // Todo, Do not really like that command_buffer_pool is there
                const size_t& width,
                const size_t& height,
                VkFormat image_format);

            std::vector<std::shared_ptr<VulkanTexture>> create_textures(
                std::shared_ptr<VulkanCommandBufferPool>& command_buffer_pool, // Todo, Do not really like that command_buffer_pool is there
                const size_t& width,
                const size_t& height,
                VkFormat image_format,
                const size_t& count);

            std::shared_ptr<VulkanPipelineManager> create_pipeline_manager();

            std::shared_ptr<VulkanSwapChainRenderTarget> create_render_target(
                std::vector<VulkanSwapChainImageTuple>& image_views,
                VkFormat image_format,
                VkExtent2D extent);

            std::shared_ptr<VulkanSwapChain> create_swap_chain(std::shared_ptr<Window>& window);

            void wait_idle();

            uint32_t find_memory_type(uint32_t type_filter, VkMemoryPropertyFlags properties);

            VulkanQueueFamilyIndices find_physical_queue_families() { return VulkanDeviceChooser::find_queue_families(physical_device, surface); }
            VulkanSwapChainSupportDetails get_swap_chain_support() { return VulkanDeviceChooser::query_swap_chain_support(physical_device, surface); }

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

            void collect_garbage();

            void destroy(VulkanInstance& instance);

            VkFormat find_depth_format();
    };
}

#endif