#include "vulkan_debug_messenger.h"
#include "vulkan_instance.h"

namespace bebone::gfx::vulkan {
    static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
        VkDebugUtilsMessageSeverityFlagBitsEXT message_severity,
        VkDebugUtilsMessageTypeFlagsEXT message_type,
        const VkDebugUtilsMessengerCallbackDataEXT *callback,
        void *user_ptr
    ) {
        std::ignore = message_severity;
        std::ignore = message_type;
        std::ignore = user_ptr;

        std::cerr << "validation layer: " << callback->pMessage << std::endl;

        return VK_FALSE;
    }

    VkResult CreateDebugUtilsMessengerEXT(
        VkInstance instance,
        const VkDebugUtilsMessengerCreateInfoEXT *create_info,
        const VkAllocationCallbacks *allocator,
        VkDebugUtilsMessengerEXT *debug_messenger
    ) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");

        if (func != nullptr)
            return func(instance, create_info, allocator, debug_messenger);

        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    void DestroyDebugUtilsMessengerEXT(
        VkInstance instance,
        VkDebugUtilsMessengerEXT debug_messenger,
        const VkAllocationCallbacks *allocator
    ) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");

        if (func != nullptr)
            func(instance, debug_messenger, allocator);
    }

    void VulkanDebugMessenger::populate_debug_messenger_create_info(VkDebugUtilsMessengerCreateInfoEXT &create_info) {
        create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        create_info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        create_info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        create_info.pfnUserCallback = debug_callback;
        create_info.pUserData = nullptr;  // Optional
    }

    VulkanDebugMessenger::VulkanDebugMessenger(VulkanInstance& instance) : vulkan_instance(instance) {
        VkDebugUtilsMessengerCreateInfoEXT create_info;

        populate_debug_messenger_create_info(create_info);

        if (CreateDebugUtilsMessengerEXT(vulkan_instance.get_instance(), &create_info, nullptr, &debug_messenger) != VK_SUCCESS) {
            throw std::runtime_error("failed to set up debug messenger!");
        }
    }

    VulkanDebugMessenger::~VulkanDebugMessenger() {
        DestroyDebugUtilsMessengerEXT(vulkan_instance.get_instance(), debug_messenger, nullptr);
    }
}

