#ifndef _BEBONE_RENDERER_VULKAN_RENDERER_H_
#define _BEBONE_RENDERER_VULKAN_RENDERER_H_

#include "../irenderer.h"
#include "../irender_graph.h"
#include "vulkan_render_graph_impl.h"
#include "vulkan_triangle_mesh.h"
#include "vulkan_triangle_mesh_builder.h"
#include "../pbr_render_graph.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanRenderer : public IRenderer {
        private:
            std::shared_ptr<Window> window;

            std::shared_ptr<VulkanInstance> instance;
            std::shared_ptr<VulkanDevice> device;
            std::shared_ptr<VulkanSwapChain> swap_chain;

            std::vector<std::shared_ptr<IMesh>> mesh_pool;

            std::shared_ptr<IRenderGraph> render_graph;

            std::shared_ptr<ICamera> camera;

        protected:
            void handle_resize(const Vec2i& new_size) override;

        public:
            VulkanRenderer(std::shared_ptr<gfx::Window>& window);
            ~VulkanRenderer() override;

            MeshHandle load_mesh(const std::string& file_path) override;
            MeshHandle create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) override;

            void render(const MeshHandle& handle, const Transform& transform = {}) override;

            void present() override;

            std::shared_ptr<IRenderGraphImpl> create_render_graph_impl() override;
    };
}

#endif
