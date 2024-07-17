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

        public:
            VulkanTextureManager(
                const std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<VulkanProgramManager>& program_manager);

            std::shared_ptr<ITexture> create_texture() override;
            std::shared_ptr<ITexture> load_texture_from_file(const std::string& file_path) override;
    };
}

#endif
