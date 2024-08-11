#ifndef _BEBONE_RENDERER_VULKAN_MESH_MANAGER_H_
#define _BEBONE_RENDERER_VULKAN_MESH_MANAGER_H_

#include "imesh_manager.h"
#include "vulkan_program_manager.h"
#include "vulkan_material_impl.h"

#include "mesh/imesh_impl.h"
#include "mesh/obj_mesh_loader.h"
#include "mesh/quad_mesh_generator.h"
#include "mesh/cube_mesh_generator.h"

#include "vulkan_triangle_mesh_impl.h"
#include "vulkan_triangle_mesh_builder.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanMeshManager : public IMeshManager {
        private:
            std::shared_ptr<VulkanDevice> device;

            std::vector<std::shared_ptr<IMesh>> meshes;

            MeshHandle quad_mesh;
            MeshHandle cube_mesh;

        public:
            VulkanMeshManager(const std::shared_ptr<VulkanDevice>& device);

            MeshHandle load_mesh(const std::string& file_path) override;
            MeshHandle generate_mesh(const std::shared_ptr<IMeshGenerator>& mesh_generator) override;
            MeshHandle create_mesh(const std::vector<Vertex>& vertices, const std::vector<u32>& indicies) override;

            void draw_indexed(ICommandEncoder* encoder, const MeshHandle& handle) override;

            MeshHandle get_default_quad() override;
            MeshHandle get_default_cube() override;

            [[nodiscard]] std::optional<std::shared_ptr<IMesh>> get_mesh(const MeshHandle& handle) const override;
    };
}

#endif
