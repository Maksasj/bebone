#include "vulkan_material_manager.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanMaterialManager::VulkanMaterialManager(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanProgramManager>& program_manager
    ) : device(device), program_manager(program_manager) {

    }

    std::optional<std::shared_ptr<IMaterial>> VulkanMaterialManager::get_material(const MaterialHandle& handle) const {
        for(auto& material : materials)
            if(static_cast<MaterialHandle>(material->get_handle()) == handle)
                return material;

        return std::nullopt;
    }
}
