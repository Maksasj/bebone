#ifndef _BEBONE_RENDERER_VULKAN_TEXTURE_H_
#define _BEBONE_RENDERER_VULKAN_TEXTURE_H_

#include "../itexture.h"

namespace bebone::renderer {
    class VulkanTexture : public ITexture {
        private:
            std::shared_ptr<gfx::VulkanTexture> texture;
            size_t gpu_handle; // Todo, Handle should be same for ALL pipelines

        public:
            VulkanTexture(const std::string& file_path, std::shared_ptr<gfx::VulkanDevice>& device);

            std::shared_ptr<gfx::VulkanTexture>& get_texture();
    };
}

#endif
