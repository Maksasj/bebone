#include "renderer_factory.h"

#include "vulkan/vulkan_renderer.h"

namespace bebone::renderer {
    std::shared_ptr<IRenderer> RendererFactory::create_renderer(std::shared_ptr<gfx::Window>& window) {
        const auto api = window->get_api();

        if(api == OpenGL) {
            LOG_ERROR("OpenGL renderer is not implemented");
            throw std::runtime_error("Not implemented");
        } else if(api == Vulkan) {
            return std::make_shared<VulkanRenderer>(window);
        }
    }

    std::pair<std::shared_ptr<Window>, std::shared_ptr<IRenderer>> create_window_renderer(const std::string& title, const int& width, const int& height, const GfxAPI& gfx_api, const WindowProperties& properties) {
        auto window = WindowFactory::create_window(title, width, height, gfx_api, properties);
        auto renderer = RendererFactory::create_renderer(window);
        return { window, renderer };
    }
}
