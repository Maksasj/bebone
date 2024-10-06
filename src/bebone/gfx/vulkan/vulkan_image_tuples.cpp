#include "vulkan_image_tuples.h"

#include "vulkan_image.h"
#include "vulkan_image_view.h"
#include "vulkan_sampler.h"

namespace bebone::gfx {
        VulkanSwapChainImageTuple::VulkanSwapChainImageTuple(
            unique_ptr<VulkanImage>& image,
            unique_ptr<VulkanImageView>& view
        ) : image(std::move(image)), view(std::move(view))  {

        }

        std::optional<std::unique_ptr<VulkanImage>> VulkanSwapChainImageTuple::get_image() {
            LOG_WARNING("TODO get_image returning nullopt");
            // return image;
            return std::nullopt;
        }

        std::optional<std::unique_ptr<VulkanImageView>> VulkanSwapChainImageTuple::get_view() {
            LOG_WARNING("TODO get_view returning nullopt");
            // return view;
            return std::nullopt;
        }

        std::optional<std::unique_ptr<VulkanDeviceMemory>> VulkanSwapChainImageTuple::get_memory() {
            return std::nullopt;
        }

        std::optional<std::unique_ptr<VulkanSampler>> VulkanSwapChainImageTuple::get_sampler() {
            return std::nullopt;
        }

        VulkanAttachmentType VulkanSwapChainImageTuple::get_type() const {
            return Color;
        }

        /*
        void VulkanSwapChainImageTuple::destroy(VulkanDevice &device)  {
            view->destroy(device);

            mark_destroyed();
        }
         */

        VulkanDepthImageTuple::VulkanDepthImageTuple(
            unique_ptr<VulkanImage>& image,
            unique_ptr<VulkanImageView>& view,
            unique_ptr<VulkanDeviceMemory>& memory
        ) : image(std::move(image)), view(std::move(view)), memory(std::move(memory)) {

        }

        std::optional<std::unique_ptr<VulkanImage>> VulkanDepthImageTuple::get_image() {
            LOG_WARNING("TODO get_image returning nullopt");
            // return image;
            return std::nullopt;
        }

        std::optional<std::unique_ptr<VulkanImageView>> VulkanDepthImageTuple::get_view() {
            LOG_WARNING("TODO get_view returning nullopt");
            // return view;
            return std::nullopt;
        }

        std::optional<std::unique_ptr<VulkanDeviceMemory>> VulkanDepthImageTuple::get_memory() {
            LOG_WARNING("TODO get_memory returning nullopt");
            // return memory;
            return std::nullopt;
        }

        std::optional<std::unique_ptr<VulkanSampler>> VulkanDepthImageTuple::get_sampler() {
            return std::nullopt;
        }

        VulkanAttachmentType VulkanDepthImageTuple::get_type() const {
            return Depth;
        }

        /*
        void VulkanDepthImageTuple::destroy(VulkanDevice &device) {
            image->destroy(device);
            view->destroy(device);
            memory->destroy(device);

            mark_destroyed();
        }
         */

        VulkanImageMemoryTuple::VulkanImageMemoryTuple(
            unique_ptr<VulkanImage>& image,
            unique_ptr<VulkanDeviceMemory>& memory
        ) : image(std::move(image)), memory(std::move(memory)) {

        }

        /*
        void VulkanImageMemoryTuple::destroy(VulkanDevice &device) {
            image->destroy(device);
            memory->destroy(device);

            mark_destroyed();
        }
         */
}
