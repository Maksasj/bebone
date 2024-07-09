#include "vulkan_pass_factory.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanPassFactory::VulkanPassFactory() {

    }

    std::shared_ptr<IPresentPass> VulkanPassFactory::create_present_pass(const std::string& pass_name) {
        return std::make_shared<VulkanPresentPass>(pass_name);
    }
    std::shared_ptr<IGeometryPass> VulkanPassFactory::create_geometry_pass(const std::string& pass_name) {
        return std::make_shared<VulkanGeometryPass>(pass_name);
    }
}
