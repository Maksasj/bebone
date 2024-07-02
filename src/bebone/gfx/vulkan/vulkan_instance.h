#ifndef _BEBONE_GFX_VULKAN_INSTANCE_H_
#define _BEBONE_GFX_VULKAN_INSTANCE_H_

#include <memory>

#include "../gfx_backend.h"
#include "../window/vulkan_window.h"
#include "vulkan_debug_messenger.h"

namespace bebone::gfx {
    class VulkanDevice;

    class VulkanInstance : private core::NonCopyable {
        private:
            VkInstance instance;

            std::unique_ptr<VulkanDebugMessenger> debug_messenger;
            std::vector<std::shared_ptr<VulkanDevice>> child_devices;

            bool check_validation_layer_support();
            static void has_gflw_required_instance_extensions();
            static std::vector<const char *> get_required_extensions();

        public:
            bool const static enable_validation_layers = true;

            VkInstance& get_instance();

            VulkanInstance();

            std::shared_ptr<VulkanDevice> create_device(std::shared_ptr<Window>& window);

            const std::vector<const char *> validation_layers = { "VK_LAYER_KHRONOS_validation" };

            static std::shared_ptr<VulkanInstance> create_instance() {
                return std::make_shared<VulkanInstance>();
            }

            void destroy_all(std::shared_ptr<VulkanDevice>& device);

            void destroy();
    };
}

#endif
