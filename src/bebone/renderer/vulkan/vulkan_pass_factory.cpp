#include "vulkan_pass_factory.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanPassFactory::VulkanPassFactory(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanSwapChain>& swap_chain
    ) : device(device), swap_chain(swap_chain) {

    }

    std::shared_ptr<IPresentPass> VulkanPassFactory::create_present_pass(const std::string& pass_name, const Vec2i& viewport) {
        auto render_pass = swap_chain->render_pass;
        auto impl = std::make_shared<VulkanPassImpl>(render_pass);

        return std::make_shared<IPresentPass>(impl, pass_name, viewport);
    }

    std::shared_ptr<IDeferredGPass> VulkanPassFactory::create_deferred_g_pass(const std::string& pass_name, const Vec2i& viewport) {
        auto vv = VkExtent2D { static_cast<uint32_t>(viewport.x), static_cast<uint32_t>(viewport.y) };
        auto render_pass = device->create_render_pass(vv, {
            VulkanAttachmentDesc::color2D(vv, { .format = VK_FORMAT_R32G32B32A32_SFLOAT }), /* position */
            VulkanAttachmentDesc::color2D(vv, { .format = VK_FORMAT_R32G32B32A32_SFLOAT }), /* normals  */
            VulkanAttachmentDesc::color2D(vv, { .format = VK_FORMAT_R32G32B32A32_SFLOAT }), /* albedo   */
            VulkanAttachmentDesc::color2D(vv, { .format = VK_FORMAT_R32G32B32A32_SFLOAT }), /* specular */
            VulkanAttachmentDesc::depth2D(vv, { .format = device->find_depth_format() }),   /* depth    */
        });
        auto impl = std::make_shared<VulkanPassImpl>(render_pass);

        return std::make_shared<IDeferredGPass>(impl, pass_name, viewport);
    }
}
