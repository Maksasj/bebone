#ifndef _BEBONE_GFX_VULKAN_ATTACHMENT_H_
#define _BEBONE_GFX_VULKAN_ATTACHMENT_H_

#include <optional>

#include "../gfx_backend.h"

#include "vulkan_wrapper.tpp"

namespace bebone::gfx {
    using namespace bebone::core;

    struct VulkanDepthAttachmentDescription {
        VkAttachmentDescriptionFlags flags = 0;
        VkFormat format = VK_FORMAT_UNDEFINED;
        VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT;
        VkAttachmentLoadOp loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        VkAttachmentStoreOp storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        VkAttachmentLoadOp stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        VkAttachmentStoreOp stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        VkImageLayout initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        VkImageLayout finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    };

    struct VulkanColorAttachmentDescription {
        VkAttachmentDescriptionFlags flags = 0;
        VkFormat format = VK_FORMAT_UNDEFINED;
        VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT;
        VkAttachmentLoadOp loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        VkAttachmentStoreOp storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        VkAttachmentLoadOp stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        VkAttachmentStoreOp stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        VkImageLayout initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        VkImageLayout finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    };

    enum VulkanAttachmentType {
        Depth,
        Color
    };

    struct VulkanAttachmentDesc {
        VkAttachmentDescription description;
        VulkanAttachmentType type;
        VkImageLayout layout;
        VkExtent3D extent;

        static VulkanAttachmentDesc depth3D(VkExtent3D extent, VulkanDepthAttachmentDescription description = {});
        static VulkanAttachmentDesc depth2D(VkExtent2D extent, VulkanDepthAttachmentDescription description = {});

        static VulkanAttachmentDesc color3D(VkExtent3D extent, VulkanColorAttachmentDescription description = {});
        static VulkanAttachmentDesc color2D(VkExtent2D extent, VulkanColorAttachmentDescription description = {});
    };
}

#endif
