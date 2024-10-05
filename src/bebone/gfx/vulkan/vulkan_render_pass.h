#ifndef _BEBONE_GFX_VULKAN_RENDER_PASS_H_
#define _BEBONE_GFX_VULKAN_RENDER_PASS_H_

#include <array>

#include "../gfx_backend.h"

#include "vulkan_device.h"
#include "vulkan_wrapper.tpp"
#include "vulkan_attachment.h"

namespace bebone::gfx {
    class VulkanRenderPass : public VulkanWrapper<VkRenderPass> {
        private:
            vector<VulkanAttachmentDesc> attachments;

            size_t depth_attachment_index;
            bool has_depth_attachment_flag;

            size_t color_attachment_count;

            // Todo, not sure is this needed there
            VkExtent2D extent;

        public:
            VulkanRenderPass(VulkanDevice& device, VkExtent2D extent, const std::vector<VulkanAttachmentDesc>& attachments);

            std::optional<VulkanAttachmentDesc> get_depth_attachment() const;

            const size_t& get_color_attachments_count() const;
            const vector<VulkanAttachmentDesc>& get_attachments() const;
            const VkExtent2D& get_extent() const;

            // void destroy(VulkanDevice& device) override;
    };
}

#endif
