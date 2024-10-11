#include "vulkan_attachment.h"

namespace bebone::gfx {
    VulkanAttachmentDesc VulkanAttachmentDesc::depth3D(VkExtent3D extent, VulkanDepthAttachmentDescription description) {
        return VulkanAttachmentDesc {
            .description {
                .flags = description.flags,
                .format = description.format,
                .samples = description.samples,
                .loadOp = description.loadOp,
                .storeOp = description.storeOp,
                .stencilLoadOp = description.stencilLoadOp,
                .stencilStoreOp = description.stencilStoreOp,
                .initialLayout = description.initialLayout,
                .finalLayout = description.finalLayout,
            },
            .type = Depth,
            .layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
            .extent = extent
        };
    }

    VulkanAttachmentDesc VulkanAttachmentDesc::depth2D(VkExtent2D extent, VulkanDepthAttachmentDescription description) {
        return VulkanAttachmentDesc::depth3D({ extent.width, extent.height, 1 }, description);
    }

    VulkanAttachmentDesc VulkanAttachmentDesc::color3D(VkExtent3D extent, VulkanColorAttachmentDescription description) {
        return VulkanAttachmentDesc {
            .description {
                .flags = description.flags,
                .format = description.format,
                .samples = description.samples,
                .loadOp = description.loadOp,
                .storeOp = description.storeOp,
                .stencilLoadOp = description.stencilLoadOp,
                .stencilStoreOp = description.stencilStoreOp,
                .initialLayout = description.initialLayout,
                .finalLayout = description.finalLayout,
            },
            .type = Color,
            .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
            .extent = extent
        };
    }

    VulkanAttachmentDesc VulkanAttachmentDesc::color2D(VkExtent2D extent, VulkanColorAttachmentDescription description) {
        return VulkanAttachmentDesc::color3D({ extent.width, extent.height, 1 }, description);
    }
}
