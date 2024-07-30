#include "vulkan_material.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanMaterial::VulkanMaterial(
        std::shared_ptr<VulkanDevice>& device,
        std::shared_ptr<VulkanProgramManager>& program_manager,
        void* properties,
        const size_t& size
    ) : device(device), size(size) {
        auto pipeline_manager = program_manager->get_pipeline_manager();

        material_uniform_buffer = device->create_buffer_memory(size);
        handle = static_cast<MaterialHandle>(pipeline_manager->bind_uniform_buffer(device, material_uniform_buffer));

        material_uniform_buffer->upload_data(device, properties, size);
    }

    const MaterialHandle& VulkanMaterial::get_handle() const {
        return handle;
    }

    void VulkanMaterial::set_properties(const void* properties) {
        material_uniform_buffer->upload_data(device, properties, size);
    }
}
