#include "vulkan_attachment_impl.h"

namespace bebone::renderer {
    VulkanAttachmentImpl::VulkanAttachmentImpl(
        const std::vector<TextureHandle>& handles
    ) : handles(handles) {

    }

    const std::vector<TextureHandle>& VulkanAttachmentImpl::get_handles() const {
        return handles;
    }
}
