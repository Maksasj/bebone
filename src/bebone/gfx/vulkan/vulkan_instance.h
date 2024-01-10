#ifndef _BEBONE_GFX_VULKAN_VULKAN_INSTANCE_H_
#define _BEBONE_GFX_VULKAN_VULKAN_INSTANCE_H_

#include <memory>

#include "../gfx_backend.h"
#include "../window/vulkan_window.h"
#include "vulkan_debug_messenger.h"

namespace bebone::gfx::vulkan {
    class VulkanDevice;

    class VulkanInstance : private core::NonCopyable {
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

            std::shared_ptr<VulkanDevice> create_device(std::shared_ptr<Window>& window);

            const std::vector<const char *> validationLayers = { "VK_LAYER_KHRONOS_validation" };

            static std::shared_ptr<VulkanInstance> create_instance() {
                return std::make_shared<VulkanInstance>();
            }

            void destroy() {
                if(enableValidationLayers)
                    debugMessenger = nullptr;

                vkDestroyInstance(instance, nullptr);
            }
    };
}

#endif
