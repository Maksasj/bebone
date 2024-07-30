#ifndef _BEBONE_RENDERER_VULKAN_MATERIAL_MANAGER_H_
#define _BEBONE_RENDERER_VULKAN_MATERIAL_MANAGER_H_

#include "imaterial_manager.h"
#include "vulkan_program_manager.h"
#include "vulkan_material_impl.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanMaterialManager : public IMaterialManager {
        private:
            std::shared_ptr<VulkanDevice> device;
            std::shared_ptr<VulkanProgramManager> program_manager;

            std::shared_ptr<VulkanMaterialImpl> default_material_ptr;
            std::vector<std::shared_ptr<VulkanMaterialImpl>> materials;

        public:
            VulkanMaterialManager(
                const std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<VulkanProgramManager>& program_manager);

            MaterialHandle default_material() override;
            MaterialHandle create_material(void* properties, const size_t& size) override;

            [[nodiscard]] std::optional<std::shared_ptr<IMaterialImpl>> get_material(const MaterialHandle& handle) const override;
    };
}

#endif
