#include "vulkan_image_tuples.h"

#include "vulkan_image.h"
#include "vulkan_image_view.h"

namespace bebone::gfx {
        VulkanSwapChainImageTuple::VulkanSwapChainImageTuple(
            const shared_ptr<VulkanImage>& image,
            const shared_ptr<VulkanImageView>& view
        ) : image(image), view(view)  {

        }

        std::optional<std::shared_ptr<VulkanImage>> VulkanSwapChainImageTuple::get_image() {
            return image;
        }

        std::optional<std::shared_ptr<VulkanImageView>> VulkanSwapChainImageTuple::get_view() {
            return view;
        }

        std::optional<std::shared_ptr<VulkanDeviceMemory>> VulkanSwapChainImageTuple::get_memory() {
            return std::nullopt;
        }

        std::optional<std::shared_ptr<VulkanSampler>> VulkanSwapChainImageTuple::get_sampler() {
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
            const shared_ptr<VulkanImage>& image,
            const shared_ptr<VulkanImageView>& view,
            const shared_ptr<VulkanDeviceMemory>& memory
        ) : image(image), view(view), memory(memory) {

        }

        std::optional<std::shared_ptr<VulkanImage>> VulkanDepthImageTuple::get_image() {
            return image;
        }

        std::optional<std::shared_ptr<VulkanImageView>> VulkanDepthImageTuple::get_view() {
            return view;
        }

        std::optional<std::shared_ptr<VulkanDeviceMemory>> VulkanDepthImageTuple::get_memory() {
            return memory;
        }

        std::optional<std::shared_ptr<VulkanSampler>> VulkanDepthImageTuple::get_sampler() {
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
            const shared_ptr<VulkanImage>& image,
            const shared_ptr<VulkanDeviceMemory>& memory
        ) : image(image), memory(memory) {

        }

        /*
        void VulkanImageMemoryTuple::destroy(VulkanDevice &device) {
            image->destroy(device);
            memory->destroy(device);

            mark_destroyed();
        }
         */
}
