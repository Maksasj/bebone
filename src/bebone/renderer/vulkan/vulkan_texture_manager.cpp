#include "vulkan_texture_manager.h"

namespace bebone::renderer {
    VulkanTextureManager::VulkanTextureManager(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanProgramManager>& program_manager
    ) : device(device), program_manager(program_manager) {

    }

    std::shared_ptr<ITexture> VulkanTextureManager::create_texture() {

    }

    std::shared_ptr<ITexture> VulkanTextureManager::load_texture_from_file(const std::string& file_path) {
        auto texture = std::make_shared<renderer::VulkanTexture>(file_path, device);
        program_manager->bind_texture(texture);
        return texture;
    }
}
