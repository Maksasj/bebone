#ifndef _BEBONE_RENDERER_VULKAN_MESH_MANAGER_H_
#define _BEBONE_RENDERER_VULKAN_MESH_MANAGER_H_

#include "imesh_manager.h"
#include "vulkan_program_manager.h"
#include "vulkan_material_impl.h"
#include "mesh/imesh.h"

#include "vulkan_triangle_mesh.h"
#include "vulkan_triangle_mesh_builder.h"

#include "mesh/obj_mesh_loader.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanMeshManager : public IMeshManager {
    private:
        std::shared_ptr<VulkanDevice> device;

        std::vector<std::shared_ptr<VulkanTriangleMesh>> meshes;

    public:
        VulkanMeshManager(const std::shared_ptr<VulkanDevice>& device);

        MeshHandle load_mesh(const std::string& file_path) override;
        MeshHandle create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) override;

        void draw_indexed(ICommandEncoder* encoder, const MeshHandle& handle) override;

        [[nodiscard]] std::optional<std::shared_ptr<IMesh>> get_mesh(const MeshHandle& handle) const override;
    };
}

#endif
