#include "vulkan_geometry_pass.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    // Geometry pass
    VulkanGeometryPass::VulkanGeometryPass(const std::string& pass_name) : IGeometryPass(pass_name) {

    }

    void VulkanGeometryPass::record(ICommandEncoder* encoder) {

    }

    void VulkanGeometryPass::reset() {

    }
}
