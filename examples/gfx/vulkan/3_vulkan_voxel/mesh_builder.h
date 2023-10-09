#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
#define OMNI_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

#include "handles.h"
#include "transform.h"

#include "mesh.h"

using namespace bebone::gfx;
using namespace bebone::core;

class MeshBuilder {
    private:
        std::vector<Vertex> vertices;
        std::vector<int> indices;
        int indicesOffset;

    public:
        MeshBuilder() : indicesOffset(0) {

        }

        void append(std::vector<Vertex>& _vertices, std::vector<u32>& _indices, const Vec3f& posOffset) {
            for(auto vertex : _vertices) {
                vertex.pos += posOffset;
                vertices.push_back(vertex);
            }

            u32 maxIndex = 0;
            for(const auto& index : _indices) {
                indices.push_back(index + indicesOffset);

                if(index > maxIndex)
                    maxIndex = index;    
            }

            indicesOffset += maxIndex + 1;
        }

        std::unique_ptr<Mesh> build(VulkanRenderer& renderer) {
            return  std::make_unique<Mesh>(renderer, vertices, indices);
        }
};

std::vector<Vertex> QUAD_MESH_UP_VERTEX_DATA = {
    {{ 0.5f, 0.5f,  0.5f},  {0.4f, 0.0f,0.4f}},
    {{-0.5f, 0.5f,  0.5f},  {0.4f, 0.0f,0.4f}},
    {{-0.5f, 0.5f, -0.5f},  {0.4f, 0.0f,0.4f}},
    {{ 0.5f, 0.5f, -0.5f},  {0.4f, 0.0f,0.4f}}
};

std::vector<Vertex> QUAD_MESH_DOWN_VERTEX_DATA = {
    {{ 0.5f, -0.5f,  0.5f},  {1.0f, 0.0f, 1.0f}},
    {{-0.5f, -0.5f,  0.5f},  {1.0f, 0.0f, 1.0f}},
    {{-0.5f, -0.5f, -0.5f},  {1.0f, 0.0f, 1.0f}},
    {{ 0.5f, -0.5f, -0.5f},  {1.0f, 0.0f, 1.0f}}
};

std::vector<Vertex> QUAD_MESH_LEFT_VERTEX_DATA = {
    {{0.5f,  0.5f,  0.5f},  {0.6f, 0.0f, 0.6f}},
    {{0.5f, -0.5f,  0.5f},  {0.6f, 0.0f, 0.6f}},
    {{0.5f, -0.5f, -0.5f},  {0.6f, 0.0f, 0.6f}},
    {{0.5f,  0.5f, -0.5f},  {0.6f, 0.0f, 0.6f}}
};

std::vector<Vertex> QUAD_MESH_RIGHT_VERTEX_DATA = {
    {{-0.5f, -0.5f,  0.5f},  {0.6f, 0.0f, 0.6f}},
    {{-0.5f,  0.5f,  0.5f},  {0.6f, 0.0f, 0.6f}},
    {{-0.5f,  0.5f, -0.5f},  {0.6f, 0.0f, 0.6f}},
    {{-0.5f, -0.5f, -0.5f},  {0.6f, 0.0f, 0.6f}}
};

std::vector<Vertex> QUAD_MESH_FORWARD_VERTEX_DATA = {
    {{ 0.5f, -0.5f, 0.5f},  {0.6f, 0.0f, 0.6f}},
    {{ 0.5f,  0.5f, 0.5f},  {0.6f, 0.0f, 0.6f}},
    {{-0.5f,  0.5f, 0.5f},  {0.6f, 0.0f, 0.6f}},
    {{-0.5f, -0.5f, 0.5f},  {0.6f, 0.0f, 0.6f}}
};

std::vector<Vertex> QUAD_MESH_BACK_VERTEX_DATA = {
    {{ 0.5f,  0.5f, -0.5f},  {0.6f, 0.0f, 0.6f}},
    {{ 0.5f, -0.5f, -0.5f},  {0.6f, 0.0f, 0.6f}},
    {{-0.5f, -0.5f, -0.5f},  {0.6f, 0.0f, 0.6f}},
    {{-0.5f,  0.5f, -0.5f},  {0.6f, 0.0f, 0.6f}}
};

std::vector<u32> QUAD_MESH_INDICES_DATA = {
    0, 1, 3, 1, 2, 3
};


#endif
