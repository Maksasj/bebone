#include "vulkan_attachment.h"

namespace bebone::gfx {
    VulkanAttachment VulkanAttachment::depth(VulkanDepthAttachmentDescription description) {
        return VulkanAttachment {
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
            .layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
        };
    }

    VulkanAttachment VulkanAttachment::color(VulkanColorAttachmentDescription description) {
        return VulkanAttachment {
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
            .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
        };
    }
}
