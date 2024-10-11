#ifndef _BEBONE_RENDERER_VULKAN_MATERIAL_IMPL_H_
#define _BEBONE_RENDERER_VULKAN_MATERIAL_IMPL_H_

#include "imaterial_impl.h"
#include "vulkan_program_manager.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanMaterialImpl : public IMaterialImpl {
        private:
            std::shared_ptr<VulkanDevice> device;

        private:
            std::shared_ptr<VulkanBufferMemory> material_uniform_buffer;

            const size_t size;
            MaterialHandle handle;

        public:
            VulkanMaterialImpl(
                std::shared_ptr<VulkanDevice>& device,
                std::shared_ptr<VulkanProgramManager>& program_manager,
                void* properties,
                const size_t& size);

            void set_properties(const void* properties) override;

            [[nodiscard]] MaterialHandle get_handle() const override;
    };
}

#endif
