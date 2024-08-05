#include "vulkan_pass_impl.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanPassImpl::VulkanPassImpl(const std::shared_ptr<VulkanRenderPass>& render_pass) : render_pass(render_pass) {

    }

    std::shared_ptr<VulkanRenderPass> VulkanPassImpl::get_vulkan_pass() const {
        return render_pass;
    }
}
