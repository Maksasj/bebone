#ifndef _BEBONE_RENDERER_VULKAN_MATERIAL_H_
#define _BEBONE_RENDERER_VULKAN_MATERIAL_H_

#include "../imaterial.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanMaterial : public IMaterial {
        private:
            std::shared_ptr<VulkanBufferMemoryTuple> material_uniform_buffer;

        // camera_ubo = device->create_buffer_memory(sizeof(VulkanDeferredGPassCameraData));
        // camera_ubo_handles  = pipeline_manager->bind_uniform_buffers(device, camera_ubo);

        public:
            VulkanMaterial();

            const MaterialHandle& get_handle() const override;
    };
}

#endif
