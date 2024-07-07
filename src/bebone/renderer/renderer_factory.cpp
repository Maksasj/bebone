#include "renderer_factory.h"

#include "opengl/opengl_renderer.h"
#include "vulkan/vulkan_renderer.h"

namespace bebone::renderer {
    std::shared_ptr<IRenderer> RendererFactory::create_renderer(std::shared_ptr<gfx::Window>& window) {
        const auto api = window->get_api();

        if(api == OpenGL) {
            return std::make_shared<GLRenderer>(window);
        } else if(api == Vulkan) {
            return std::make_shared<VulkanRenderer>(window);
        }

        throw std::runtime_error("Not implemented");
    }
}
