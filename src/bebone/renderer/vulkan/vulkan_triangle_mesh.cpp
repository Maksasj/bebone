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

    void VulkanTriangleMesh::bind() {

    }
}
