#ifndef _BEBONE_GFX_VULKAN_VULKAN_DEBUG_MESSENGER_H_
#define _BEBONE_GFX_VULKAN_VULKAN_DEBUG_MESSENGER_H_

#include "../gfx_backend.h"

namespace bebone::gfx::vulkan {
    class VulkanInstance;

    class VulkanDebugMessenger : private core::NonCopyable {
        private:
            VulkanInstance& vulkanInstance;

            VkDebugUtilsMessengerEXT debugMessenger;

        public:
            static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT &createInfo);

            VulkanDebugMessenger(VulkanInstance& vulkanInstance);
            ~VulkanDebugMessenger();
    };
}


#endif
