#ifndef _BEBONE_RENDERER_VULKAN_MATERIAL_H_
#define _BEBONE_RENDERER_VULKAN_MATERIAL_H_

#include "imaterial.h"
#include "vulkan_program_manager.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanMaterial : public IMaterial {
        private:
            std::shared_ptr<VulkanDevice> device;

        private:
            std::shared_ptr<VulkanBufferMemoryTuple> material_uniform_buffer;

            const size_t size;
            MaterialHandle handle;

        public:
            VulkanMaterial(
                std::shared_ptr<VulkanDevice>& device,
                std::shared_ptr<VulkanProgramManager>& program_manager,
                void* properties,
                const size_t& size);

            void set_properties(const void* properties) override;

            const MaterialHandle& get_handle() const override;
    };
}

#endif
