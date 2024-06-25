#include "vulkan_image_tuples.h"

namespace bebone::gfx::vulkan {
        VulkanSwapChainImageTuple::VulkanSwapChainImageTuple(
            const shared_ptr<VulkanImage>& image,
            const shared_ptr<VulkanImageView>& view
        ) : image(image), view(view)  {

        }

        void VulkanSwapChainImageTuple::destroy(VulkanDevice &device)  {
            // Todo
        }

        VulkanDepthImageTuple::VulkanDepthImageTuple(
            const shared_ptr<VulkanImage>& image,
            const shared_ptr<VulkanImageView>& view,
            const shared_ptr<VulkanDeviceMemory>& memory
        ) : image(image), view(view), memory(memory) {

        }

        void VulkanDepthImageTuple::destroy(VulkanDevice &device) {
            // Todo
        }

        VulkanImageMemoryTuple::VulkanImageMemoryTuple(
            const shared_ptr<VulkanImage>& image,
            const shared_ptr<VulkanDeviceMemory>& memory
        ) : image(image), memory(memory) {

        }

        void VulkanImageMemoryTuple::destroy(VulkanDevice &device) {
            // Todo
        }
}
