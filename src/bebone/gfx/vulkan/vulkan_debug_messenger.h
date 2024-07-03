#ifndef _BEBONE_GFX_VULKAN_DEBUG_MESSENGER_H_
#define _BEBONE_GFX_VULKAN_DEBUG_MESSENGER_H_

#include "../gfx_backend.h"

namespace bebone::gfx {
    class VulkanInstance;

    class VulkanDebugMessenger : private core::NonCopyable {
        private:
            VulkanInstance& vulkan_instance;
            VkDebugUtilsMessengerEXT debug_messenger;

        public:
            VulkanDebugMessenger(VulkanInstance& instance);

            ~VulkanDebugMessenger();

            static void populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT &create_info);
    };
}


#endif
