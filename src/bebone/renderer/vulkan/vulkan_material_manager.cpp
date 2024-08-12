#include "vulkan_material_manager.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanMaterialManager::VulkanMaterialManager(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanProgramManager>& program_manager
    ) : device(device), program_manager(program_manager) {
        // Todo creation of default material
    }

    MaterialHandle VulkanMaterialManager::get_default_material() {
        return default_material_ptr->get_handle();
    }

    MaterialHandle VulkanMaterialManager::create_material(void* properties, const size_t& size) {
        auto impl = std::make_shared<VulkanMaterialImpl>(this->device, this->program_manager, properties, size);
        materials.push_back(std::make_shared<IMaterial>(impl));

        return impl->get_handle();
    }

    void VulkanMaterialManager::delete_material(const MaterialHandle& handle) {
        std::ignore = std::remove_if(materials.begin(), materials.end(), [&](const std::shared_ptr<IMaterial>& material) {
            return material->get_handle() == handle;
        });
    }

    std::optional<std::shared_ptr<IMaterial>> VulkanMaterialManager::get_material(const MaterialHandle& handle) const {
        if(static_cast<MaterialHandle>(default_material_ptr->get_handle()) == handle)
            return default_material_ptr;

        for(auto& material : materials)
            if(static_cast<MaterialHandle>(material->get_handle()) == handle)
                return material;

        return std::nullopt;
    }
}
