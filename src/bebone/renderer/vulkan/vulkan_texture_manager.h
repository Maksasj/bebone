#ifndef _BEBONE_RENDERER_VULKAN_TEXTURE_MANAGER_H_
#define _BEBONE_RENDERER_VULKAN_TEXTURE_MANAGER_H_

#include "itexture_manager.h"
#include "vulkan_program_manager.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanTextureManager : public ITextureManager {
        private:
            std::shared_ptr<VulkanDevice> device;
            std::shared_ptr<VulkanProgramManager> program_manager;

            std::vector<std::shared_ptr<VulkanTexture>> textures;

        public:
            VulkanTextureManager(
                const std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<VulkanProgramManager>& program_manager);

            TextureHandle create_texture(const Vec2i& extent) override;
            TextureHandle create_depth_texture(const Vec2i& extent) override;

            TextureHandle load_texture_from_file(const std::string& file_path) override;

            [[nodiscard]] std::optional<std::shared_ptr<ITexture>> get_texture(const TextureHandle& handle) const override;
    };
}

#endif
