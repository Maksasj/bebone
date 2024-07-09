#include "vulkan_render_graph.h"

namespace bebone::renderer {
    VulkanRenderGraph::VulkanRenderGraph() : IRenderGraph() {

    }

    void VulkanRenderGraph::execute() {

    }

    void VulkanRenderGraph::reset() {

    }

    std::shared_ptr<IPassFactory> VulkanRenderGraph::create_pass_factory() const {
        return std::make_shared<VulkanPassFactory>();
    }
}
