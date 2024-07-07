#include "vulkan_renderer.h"

namespace bebone::renderer {
    VulkanRenderer::VulkanRenderer(std::shared_ptr<gfx::Window>& window) : IRenderer(Vulkan) {

    }

    VulkanRenderer::~VulkanRenderer() {

    }

    SpriteHandle VulkanRenderer::load_sprite(const std::string& file_path) {

    };

    ModelHandle VulkanRenderer::load_model(const std::string& file_path) {

    };

    MeshHandle VulkanRenderer::create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) {

    };


    void VulkanRenderer::render(const SpriteHandle&, const Transform&) {

    }

    void VulkanRenderer::render(const MeshHandle&, const Transform&) {

    }

    void VulkanRenderer::render(const ModelHandle&, const Transform&) {

    }

    void VulkanRenderer::present() {

    }
}
