#include "vulkan_instance.h"
#include "vulkan_device.h"

namespace bebone::gfx {
    VulkanInstance::VulkanInstance() {
        if (enable_validation_layers && !check_validation_layer_support()) {
            LOG_ERROR("Validation layers requested, but not available");
            throw std::runtime_error("validation layers requested, but not available!");
        }

        VkApplicationInfo app_info = {};
        app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pApplicationName = "Bebone";
        app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        app_info.pEngineName = "Bebone";
        app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        app_info.apiVersion = VK_API_VERSION_1_2;

        VkInstanceCreateInfo create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        create_info.pApplicationInfo = &app_info;

        auto extensions = get_required_extensions();
        create_info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        create_info.ppEnabledExtensionNames = extensions.data();

        if (enable_validation_layers) {
            VkDebugUtilsMessengerCreateInfoEXT debug_create_info;

            create_info.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
            create_info.ppEnabledLayerNames = validation_layers.data();

            VulkanDebugMessenger::populate_debug_messenger_create_info(debug_create_info);
            create_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debug_create_info;
        } else {
            create_info.enabledLayerCount = 0;
            create_info.pNext = nullptr;
        }

        if (vkCreateInstance(&create_info, nullptr, &backend) != VK_SUCCESS) {
            LOG_ERROR("Failed to create instance");
            throw std::runtime_error("failed to create instance!");
        }

        has_gflw_required_instance_extensions();

        if(enable_validation_layers) {
            LOG_INFORMATION("Enabled vulkan validation layers");
            debug_messenger = std::make_unique<VulkanDebugMessenger>(*this);
        }

        LOG_TRACE("Created Vulkan instance");
    }

    VulkanInstance::~VulkanInstance() {
        debug_messenger.reset();

        vkDestroyInstance(backend, nullptr);
    }

    bool VulkanInstance::check_validation_layer_support() {
        uint32_t layer_count;
        vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

        auto available_layers = std::vector<VkLayerProperties>(layer_count);
        vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

        for(const char *layer_name : validation_layers) {
            bool found = false;

            for (const auto &layer_properties : available_layers) {
                if (strcmp(layer_name, layer_properties.layerName) == 0) {
                    found = true;
                    break;
                }
            }

            if (!found)
                return false;
        }

        return true;
    }

    void VulkanInstance::has_gflw_required_instance_extensions() {
        uint32_t extension_count = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);

        auto extensions = std::vector<VkExtensionProperties>(extension_count);
        vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, extensions.data());

        auto available = std::unordered_set<std::string>{};
        for(const auto &extension : extensions) {
            LOG_INFORMATION("Available extensions: {}", extension.extensionName);

            available.insert(extension.extensionName);
        }

        auto required_extensions = get_required_extensions();
        for(const auto &required : required_extensions) {
            LOG_INFORMATION("Required extensions: {}", required);

            if(available.find(required) == available.end()) {
                LOG_ERROR("Missing required GLFW extension");
                throw std::runtime_error("Missing required glfw extension");
            }
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

    std::unique_ptr<VulkanDevice> VulkanInstance::create_device(std::unique_ptr<Window>& window) {
        auto device = std::make_unique<VulkanDevice>(*this, window);

        // child_devices.push_back(device);

        return device;
    }

    /*
    void VulkanInstance::destroy_all(std::unique_ptr<VulkanDevice>& device) {
        device->destroy(*this);
    }

    void VulkanInstance::destroy() {
        if(enable_validation_layers)
            debug_messenger = nullptr;

        for(auto& child : child_devices)
            destroy_all(child);

        vkDestroyInstance(instance, nullptr);

        LOG_TRACE("Destroyed Vulkan instance");
    }
    */
}

