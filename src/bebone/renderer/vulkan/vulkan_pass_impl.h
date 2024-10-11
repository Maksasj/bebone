#ifndef _BEBONE_RENDERER_VULKAN_PASS_IMPL_H_
#define _BEBONE_RENDERER_VULKAN_PASS_IMPL_H_

#include "../ipass_impl.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanPassImpl : public IPassImpl {
        private:
            std::shared_ptr<VulkanRenderPass> render_pass;

        public:
            VulkanPassImpl(const std::shared_ptr<VulkanRenderPass>& render_pass);

            std::shared_ptr<VulkanRenderPass> get_vulkan_pass() const;
    };
}

#endif
