#ifndef MESH_H
#define MESH_H

#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
#define OMNI_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

#include "handles.h"
#include "transform.h"

using namespace bebone::gfx;
using namespace bebone::core;

class Mesh {
    private:
        size_t indexCount;

        std::unique_ptr<VertexBuffer> vertexBuffer;
        std::unique_ptr<IndexBuffer> indexBuffer;
    public:
        Mesh(VulkanRenderer& renderer, const std::vector<Vertex>& vertices, const std::vector<int>& indices) {
            indexCount = indices.size();

            vertexBuffer = std::make_unique<VertexBuffer>(renderer.create_vertex_buffer_impl(vertices));
            indexBuffer = std::make_unique<IndexBuffer>(renderer.create_index_buffer_impl(indices));
        }

        const size_t& get_index_count() const {
            return indexCount;
        }

        void bind(VulkanCommandBuffer& cmd) {
            cmd.bind_vertex_buffer(*vertexBuffer);
            cmd.bind_index_buffer(*indexBuffer);
        }
};

#endif
