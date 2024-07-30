#ifndef _BEBONE_RENDERER_VULKAN_MATERIAL_MANAGER_H_
#define _BEBONE_RENDERER_VULKAN_MATERIAL_MANAGER_H_

#include "imaterial_manager.h"
#include "vulkan_program_manager.h"
#include "vulkan_material.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanMaterialManager : public IMaterialManager {
        private:
            std::shared_ptr<VulkanDevice> device;
            std::shared_ptr<VulkanProgramManager> program_manager;

            std::shared_ptr<VulkanMaterial> default_material_ptr;
            std::vector<std::shared_ptr<VulkanMaterial>> materials;

        public:
            VulkanMaterialManager(
                const std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<VulkanProgramManager>& program_manager);

            MaterialHandle default_material() override;

            [[nodiscard]] std::optional<std::shared_ptr<IMaterial>> get_material(const MaterialHandle& handle) const override;
    };
}

#endif
