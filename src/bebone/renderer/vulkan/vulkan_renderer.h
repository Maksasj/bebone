#ifndef _BEBONE_RENDERER_VULKAN_RENDERER_H_
#define _BEBONE_RENDERER_VULKAN_RENDERER_H_

#include "../irenderer.h"

namespace bebone::renderer {
    class VulkanRenderer : public IRenderer {
        private:

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
