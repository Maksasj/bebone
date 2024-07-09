#include "vulkan_pass.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanPresentPass::VulkanPresentPass(const std::string& pass_name) : IPresentPass(pass_name) {

    }

    void VulkanPresentPass::execute() {

    }
    void VulkanPresentPass::reset() {

    }

    VulkanGeometryPass::VulkanGeometryPass(const std::string& pass_name) : IGeometryPass(pass_name) {

    }

    void VulkanGeometryPass::execute() {

    }
    void VulkanGeometryPass::reset() {

    }
}
