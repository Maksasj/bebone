#include "vulkan_mesh_manager.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanMeshManager::VulkanMeshManager(const std::shared_ptr<VulkanDevice>& device) : device(device) {

    }

    MeshHandle VulkanMeshManager::load_mesh(const std::string& file_path) {
        auto loader = std::make_shared<OBJMeshLoader>(std::make_shared<VulkanTriangleMeshBuilder>(*device));
        auto mesh = loader->load_from_file(file_path);

        meshes.push_back(static_pointer_cast<VulkanTriangleMesh>(mesh));

        return static_cast<MeshHandle>(meshes.size() - 1);
    }

    MeshHandle VulkanMeshManager::generate_mesh(const std::shared_ptr<IMeshGenerator<Vertex>>& mesh_generator) {
        auto builder = std::make_shared<VulkanTriangleMeshBuilder>(*device);
        auto mesh = mesh_generator->generate(builder);

        meshes.push_back(static_pointer_cast<VulkanTriangleMesh>(mesh));

        return static_cast<MeshHandle>(meshes.size() - 1);
    }

    MeshHandle VulkanMeshManager::create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) {
        // Todo make it this builder
        auto mesh = std::make_shared<VulkanTriangleMesh>(*device, vertices, indicies);

        meshes.push_back(static_pointer_cast<VulkanTriangleMesh>(mesh));

        return static_cast<MeshHandle>(meshes.size() - 1);
    }

    void VulkanMeshManager::draw_indexed(ICommandEncoder* encoder, const MeshHandle& handle) {
        auto vulkan_encoder = static_cast<VulkanCommandEncoder*>(encoder);
        auto cmd = vulkan_encoder->get_command_buffer();

        auto mesh = meshes[static_cast<size_t>(handle)];

        mesh->bind(encoder);
        cmd->draw_indexed(mesh->triangle_count());
    }

    std::optional<std::shared_ptr<IMesh>> VulkanMeshManager::get_mesh(const MeshHandle& handle) const {
        return meshes[static_cast<size_t>(handle)];
    }
}
