#include "vulkan_material_manager.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanMaterialManager::VulkanMaterialManager(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanProgramManager>& program_manager
    ) : device(device), program_manager(program_manager) {
        auto properties = PBRMaterialProperties {
           .albedo_handle = TextureHandle::Invalid,
           .height_handle = TextureHandle::Invalid,
           .metallic_handle = TextureHandle::Invalid,
           .roughness_handle = TextureHandle::Invalid,
        };

        default_material_ptr = std::make_shared<VulkanMaterialImpl>(
            this->device,
            this->program_manager,
            &properties,
            sizeof(PBRMaterialProperties));
    }

    MaterialHandle VulkanMaterialManager::default_material() {
        return default_material_ptr->get_handle();
    }

    std::optional<std::shared_ptr<IMaterialImpl>> VulkanMaterialManager::get_material(const MaterialHandle& handle) const {
        if(static_cast<MaterialHandle>(default_material_ptr->get_handle()) == handle)
            return default_material_ptr;

        for(auto& material : materials)
            if(static_cast<MaterialHandle>(material->get_handle()) == handle)
                return material;

        return std::nullopt;
    }
}
