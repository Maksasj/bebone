#include "vulkan_attachment_impl.h"

namespace bebone::renderer {
    VulkanAttachmentImpl::VulkanAttachmentImpl(
        std::shared_ptr<ITextureManager>& texture_manager, const Vec2i& size, const AttachmentType& type
    ) : size(size), type(type) {
        handles.reserve(3);

        if(type == Depth) {
            for(size_t i = 0; i < 3; ++i) // TODO, FIF, probably everything should be managed with handles
                handles.push_back(texture_manager->create_depth_texture(size)); // Todo VK_FORMAT_R8G8B8A8_UNORM
        } else {
            for(size_t i = 0; i < 3; ++i) // TODO, FIF, probably everything should be managed with handles
                handles.push_back(texture_manager->create_texture(size)); // Todo VK_FORMAT_R8G8B8A8_UNORM
        }
    }

    Vec2i VulkanAttachmentImpl::get_size() const {
        return size;
    }

    AttachmentType VulkanAttachmentImpl::get_type() const {
        return type;
    }

    const std::vector<TextureHandle>& VulkanAttachmentImpl::get_handles() const {
        return handles;
    }
}
