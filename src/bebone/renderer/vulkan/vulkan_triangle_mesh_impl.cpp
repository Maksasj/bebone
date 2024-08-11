#include "vulkan_triangle_mesh_impl.h"

namespace bebone::renderer {
    VulkanTriangleMeshImpl::VulkanTriangleMeshImpl(
        VulkanDevice& device, const std::vector<Vertex>& vertices, const std::vector<u32>& indices
    ) : indices_count(indices.size()), device(device) {
        this->vertices = device.create_buffer_memory_from(vertices);
        this->indices = device.create_buffer_memory_from(indices);
    }

    u64 VulkanTriangleMeshImpl::get_triangle_count() const {
        return indices_count;
    }

    u64 VulkanTriangleMeshImpl::get_vertex_count() const {
        return indices_count * 3;
    }

    void VulkanTriangleMeshImpl::bind(ICommandEncoder* encoder) {
        auto cmd = static_cast<VulkanCommandEncoder*>(encoder)->get_command_buffer();

        // Todo
        if(!vertices.has_value())
            std::cout << "Vertices are not provided\n";
        
        if(!indices.has_value())
            std::cout << "Vertices are not provided\n";

        cmd->bind_vertex_buffer(vertices.value());
        cmd->bind_index_buffer(indices.value());
    }

    void VulkanTriangleMeshImpl::bind(const std::shared_ptr<VulkanCommandBuffer>& command_buffer) {
        // Todo
        if(!vertices.has_value())
            std::cout << "Vertices are not provided\n";

        if(!indices.has_value())
            std::cout << "Vertices are not provided\n";

        command_buffer->bind_vertex_buffer(vertices.value());
        command_buffer->bind_index_buffer(indices.value());
    }
}
