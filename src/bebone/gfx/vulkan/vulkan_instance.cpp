#include "vulkan_instance.h"
#include "vulkan_device.h"

namespace bebone::gfx::vulkan {
    VkInstance& VulkanInstance::get_instance() {
        return instance;
    }

    VulkanInstance::VulkanInstance() {
        if (enable_validation_layers && !check_validation_layer_support())
            throw std::runtime_error("validation layers requested, but not available!");

        VkApplicationInfo appInfo = {};
        appInfo.type = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Bebone";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Bebone";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_2;

        VkInstanceCreateInfo createInfo = {};
        createInfo.type = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = get_required_extensions();
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        if (enable_validation_layers) {
            VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;

            createInfo.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
            createInfo.ppEnabledLayerNames = validation_layers.data();

            VulkanDebugMessenger::populate_debug_messenger_create_info(debugCreateInfo);
            createInfo.ptr_next = (VkDebugUtilsMessengerCreateInfoEXT *)&debugCreateInfo;
        } else {
            createInfo.enabledLayerCount = 0;
            createInfo.ptr_next = nullptr;
        }

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
            throw std::runtime_error("failed to create instance!");

        has_gflw_required_instance_extensions();

        if(enable_validation_layers)
            debug_messenger = std::make_unique<VulkanDebugMessenger>(*this);
    }

    bool VulkanInstance::check_validation_layer_support() {
        uint32_t layer_count;
        vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

        auto availableLayers = std::vector<VkLayerProperties>(layer_count);
        vkEnumerateInstanceLayerProperties(&layer_count, availableLayers.data());

        for(const char *layerName : validation_layers) {
            bool layerFound = false;

            for (const auto &layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound)
                return false;
        }

        return true;
    }

    // Todo remove all std::couts
    void VulkanInstance::has_gflw_required_instance_extensions() {
        uint32_t extension_count = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

        auto extensions = std::vector<VkExtensionProperties>(extension_count);
        vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, extensions.data());

        std::cout << "available extensions:" << std::endl;
        auto available = std::unordered_set<std::string>{};

        for(const auto &extension : extensions) {
            std::cout << "\t" << extension.extensionName << std::endl;
            available.insert(extension.extensionName);
        }

        std::cout << "required extensions:" << std::endl;
        auto required_extensions = get_required_extensions();

        for(const auto &required : required_extensions) {
            std::cout << "\t" << required << std::endl;
            if(available.find(required) == available.end())
                throw std::runtime_error("Missing required glfw extension");
        }
    }

    std::vector<const char *> VulkanInstance::get_required_extensions() {
        uint32_t glfw_extension_count = 0;
        const char **glfw_extensions;
        glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

        auto extensions = std::vector<const char *>(glfw_extensions, glfw_extensions + glfw_extension_count);

        if(enable_validation_layers)
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        return extensions;
    }

    std::shared_ptr<VulkanDevice> VulkanInstance::create_device(std::shared_ptr<Window>& window) {
        auto& vulkan_window = *static_cast<VulkanWindow*>(window.get());
        auto device = std::make_shared<VulkanDevice>(*this, vulkan_window);

        child_devices.push_back(device);

        return device;
    }

    void VulkanInstance::destroy_all(std::shared_ptr<VulkanDevice>& device) {
        device->destroy(*this);
    }

    void VulkanInstance::destroy() {
        if(enable_validation_layers)
            debug_messenger = nullptr;

        for(auto& child : child_devices)
            destroy_all(child);

        vkDestroyInstance(instance, nullptr);
    }
}

