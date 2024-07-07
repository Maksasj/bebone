#include "vulkan_image_tuples.h"

#include "vulkan_image.h"
#include "vulkan_image_view.h"

namespace bebone::gfx {
        VulkanSwapChainImageTuple::VulkanSwapChainImageTuple(
            const shared_ptr<VulkanImage>& image,
            const shared_ptr<VulkanImageView>& view
        ) : image(image), view(view)  {

        }

        void VulkanSwapChainImageTuple::destroy(VulkanDevice &device)  {
            view->destroy(device);

            mark_destroyed();
        }

        VulkanDepthImageTuple::VulkanDepthImageTuple(
            const shared_ptr<VulkanImage>& image,
            const shared_ptr<VulkanImageView>& view,
            const shared_ptr<VulkanDeviceMemory>& memory
        ) : image(image), view(view), memory(memory) {

        }

        void VulkanDepthImageTuple::destroy(VulkanDevice &device) {
            image->destroy(device);
            view->destroy(device);
            memory->destroy(device);

            mark_destroyed();
        }

        VulkanImageMemoryTuple::VulkanImageMemoryTuple(
            const shared_ptr<VulkanImage>& image,
            const shared_ptr<VulkanDeviceMemory>& memory
        ) : image(image), memory(memory) {

        }

        void VulkanImageMemoryTuple::destroy(VulkanDevice &device) {
            image->destroy(device);
            memory->destroy(device);

            mark_destroyed();
        }
}
