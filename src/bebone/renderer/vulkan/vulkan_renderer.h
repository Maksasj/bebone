#ifndef _BEBONE_RENDERER_VULKAN_RENDERER_H_
#define _BEBONE_RENDERER_VULKAN_RENDERER_H_

#include "../irenderer.h"

#include "vulkan_render_graph.h"
#include "vulkan_pass.h"

#include "vulkan_triangle_mesh.h"
#include "vulkan_triangle_mesh_builder.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanRenderer : public IRenderer {
        private:
            std::shared_ptr<Window> window;

            std::shared_ptr<VulkanInstance> instance;
            std::shared_ptr<VulkanDevice> device;
            std::shared_ptr<VulkanSwapChain> swap_chain;

            std::shared_ptr<VulkanPipelineManager> pipeline_manager;
            std::optional<VulkanManagedPipelineTuple> pipeline;

            std::vector<std::shared_ptr<VulkanCommandBuffer>> command_buffers;

            std::vector<std::shared_ptr<IMesh>> mesh_pool;

            std::queue<std::shared_ptr<IMesh>> render_queue;

        public:
            VulkanRenderer(std::shared_ptr<gfx::Window>& window);
            ~VulkanRenderer() override;

            SpriteHandle load_sprite(const std::string& file_path) override;
            ModelHandle load_model(const std::string& file_path) override;
            MeshHandle create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) override;

            void render(const SpriteHandle& handle, const Transform& transform = {}) override;
            void render(const MeshHandle& handle, const Transform& transform = {}) override;
            void render(const ModelHandle& handle, const Transform& transform = {}) override;

            void present() override;
    };
}

#endif
