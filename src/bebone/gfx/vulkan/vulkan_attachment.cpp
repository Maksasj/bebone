#include "vulkan_attachment.h"

namespace bebone::gfx {
    VulkanAttachmentDesc VulkanAttachmentDesc::depth(VulkanDepthAttachmentDescription description) {
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
            .layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
        };
    }

    VulkanAttachmentDesc VulkanAttachmentDesc::color(VulkanColorAttachmentDescription description) {
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
            .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
        };
    }
}
