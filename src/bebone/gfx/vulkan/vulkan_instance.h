#ifndef _BEBONE_GFX_VULKAN_INSTANCE_H_
#define _BEBONE_GFX_VULKAN_INSTANCE_H_

#include <memory>

#include "../gfx_backend.h"
#include "../window/vulkan_window.h"
#include "vulkan_debug_messenger.h"

#include "vulkan_wrapper.tpp"

namespace bebone::gfx {
    class VulkanDevice;

    class VulkanInstance : public VulkanWrapper<VkInstance>, private core::NonCopyable {
        private:
            std::unique_ptr<VulkanDebugMessenger> debug_messenger;
            std::vector<std::unique_ptr<VulkanDevice>> child_devices;

            bool check_validation_layer_support();
            static void has_gflw_required_instance_extensions();
            static std::vector<const char *> get_required_extensions();

            bool const static enable_validation_layers = true;

        public:
            VulkanInstance();
            ~VulkanInstance();

            std::unique_ptr<VulkanDevice> create_device(std::unique_ptr<Window>& window);
            const std::vector<const char *> validation_layers = { "VK_LAYER_KHRONOS_validation" };

            /*
            void destroy_all(std::unique_ptr<VulkanDevice>& device);
            void destroy();
            */
    };
}

#endif
