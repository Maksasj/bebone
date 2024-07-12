#include "vulkan_triangle_mesh.h"

namespace bebone::renderer {
    VulkanTriangleMesh::VulkanTriangleMesh(
        VulkanDevice& device, const std::vector<Vertex>& vertices, const std::vector<u32>& indices
    ) : indices_count(indices.size()), device(device) {
        this->vertices = device.create_buffer_memory_from(vertices);
        this->indices = device.create_buffer_memory_from(indices);
    }

    u64 VulkanTriangleMesh::triangle_count() const {
        return indices_count;
    }

    u64 VulkanTriangleMesh::vertex_count() const {
        return indices_count * 3;
    }

    void VulkanTriangleMesh::bind(ICommandEncoder* encoder) {
        auto cmd = static_cast<VulkanCommandEncoder*>(encoder)->get_command_buffer();

        // Todo
        if(!vertices.has_value())
            std::cout << "Vertices are not provided\n";
        
        if(!indices.has_value())
            std::cout << "Vertices are not provided\n";

        cmd->bind_vertex_buffer(vertices.value());
        cmd->bind_index_buffer(indices.value());
    }
}
