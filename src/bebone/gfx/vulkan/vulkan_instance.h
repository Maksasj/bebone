#ifndef _BEBONE_GFX_VULKAN_VULKAN_INSTANCE_H_
#define _BEBONE_GFX_VULKAN_VULKAN_INSTANCE_H_

#include <memory>

#include "../gfx_backend.h"
#include "../window/window.h"
#include "vulkan_debug_messenger.h"

namespace bebone::gfx {
    class VulkanDevice;

    class VulkanInstance {
        private:
            VkInstance instance;

            std::unique_ptr<VulkanDebugMessenger> debugMessenger;

            bool checkValidationLayerSupport();
            static void hasGflwRequiredInstanceExtensions();
            static std::vector<const char *> getRequiredExtensions();

        public:
            bool const static enableValidationLayers = true;

            void createInstance();

            VkInstance& get_instance();

            VulkanInstance();
            ~VulkanInstance();

            std::shared_ptr<VulkanDevice> create_device(Window &window);

            const std::vector<const char *> validationLayers = { "VK_LAYER_KHRONOS_validation" };

            static std::shared_ptr<VulkanInstance> create_instance() {
                return std::make_shared<VulkanInstance>();
            }
    };
}

#endif
