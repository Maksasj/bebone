#ifndef _BEBONE_RENDERER_VULKAN_RENDERER_H_
#define _BEBONE_RENDERER_VULKAN_RENDERER_H_

#include "irenderer.h"
#include "irender_graph.h"
#include "vulkan_render_graph_impl.h"
#include "vulkan_triangle_mesh_impl.h"
#include "vulkan_triangle_mesh_builder.h"
#include "pbr_render_graph.h"
#include "vulkan_texture_impl.h"

#include "vulkan_program_manager.h"
#include "vulkan_texture_manager.h"
#include "vulkan_mesh_manager.h"
#include "vulkan_material_manager.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanRenderer : public IRenderer {
        private:
            std::shared_ptr<Window> window;

            // Vulkan specific stuff
            std::shared_ptr<VulkanInstance> instance;
            std::shared_ptr<VulkanDevice> device;
            std::shared_ptr<VulkanSwapChain> swap_chain;

            // Managers
            std::shared_ptr<VulkanProgramManager> program_manager;
            std::shared_ptr<VulkanTextureManager> texture_manager;
            std::shared_ptr<VulkanMeshManager> mesh_manager;
            std::shared_ptr<VulkanMaterialManager> material_manager;

            // Render graph
            std::shared_ptr<IRenderGraph> render_graph;

            std::shared_ptr<ICamera> camera;

        protected:
            void resize_viewport(const Vec2i& new_size) override;
            std::shared_ptr<IRenderGraphImpl> create_render_graph_impl() override;

        public:
            explicit VulkanRenderer(const std::shared_ptr<gfx::Window>& window);
            ~VulkanRenderer() override;

            [[nodiscard]] std::shared_ptr<IProgramManager> get_program_manager() const override;
            [[nodiscard]] std::shared_ptr<ITextureManager> get_texture_manager() const override;
            [[nodiscard]] std::shared_ptr<IMeshManager> get_mesh_manager() const override;
            [[nodiscard]] std::shared_ptr<IMaterialManager> get_material_manager() const override;

            TextureHandle load_texture(const std::string& file_path) override;
            TextureHandle create_texture(const Vec2i& size) override;
            TextureHandle create_depth_texture(const Vec2i& size) override;
            void delete_texture(const TextureHandle& handle) override;

            MeshHandle load_mesh(const std::string& file_path) override;
            MeshHandle generate_mesh(const std::shared_ptr<IMeshGenerator>& mesh_generator) override;
            MeshHandle create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) override;

            MaterialHandle create_material(void* properties, const size_t& size) override;
            MaterialHandle get_default_material() override;

            void render(const MeshHandle& mesh_handle, const MaterialHandle& material_handle, const Vec3f& position = Vec3f::zero) override;
            void render(const MeshHandle& mesh_handle, const MaterialHandle& material_handle, const Transform& transform = {}) override;
            void present() override;

    };
}

#endif
