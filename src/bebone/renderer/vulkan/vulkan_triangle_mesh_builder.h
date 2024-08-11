#ifndef _BEBONE_RENDERER_VULKAN_TRIANGLE_MESH_BUILDER_H_
#define _BEBONE_RENDERER_VULKAN_TRIANGLE_MESH_BUILDER_H_

#include "renderer_backend.h"
#include "mesh/imesh_builder.h"
#include "vertex.h"

#include "vulkan_triangle_mesh_impl.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class VulkanTriangleMeshBuilder : public IMeshBuilder {
        protected:
            VulkanDevice& device;

            std::vector<Vertex> vertices;
            std::vector<u32> indices;
            u32 index_offset;

        public:
            VulkanTriangleMeshBuilder(VulkanDevice& device);

            void append_triangle(const VertexTriangle& triangle) override;
            void append_triangles(const VertexTriangle* triangles, const u64& count) override;

            void append_vertex(const Vertex& vertex) override;
            void append_vertices(const Vertex* vertices, const u64& count) override;

            // Todo
            void append_raw(const Vertex* verts, const u64& vert_count, const u32* inds, const u64& ind_count) override;

            void reset() override;

            std::shared_ptr<IMesh> build() override;
    };
}

#endif


