#ifndef _BEBONE_RENDERER_VULKAN_TRIANGLE_MESH_H_
#define _BEBONE_RENDERER_VULKAN_TRIANGLE_MESH_H_

#include "../renderer_backend.h"
#include "../mesh/imesh.h"
#include "../vertex.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanTriangleMesh : public IMesh {
        private:
            u64 indices_count;

        protected:
            VulkanDevice& device;

            // This should be an IVertexBuffer and IIndexBuffer
            optional<VulkanBufferMemoryTuple> vertices;
            optional<VulkanBufferMemoryTuple> indices;

        public:
            VulkanTriangleMesh(VulkanDevice& device, const std::vector<Vertex>& vertices, const std::vector<u32>& indices);

            u64 triangle_count() const override;
            u64 vertex_count() const override;

            void bind(ICommandEncoder* encoder) override;
    };
}

#endif


