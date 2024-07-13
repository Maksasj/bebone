#include "quad_mesh_generator.h"

namespace bebone::renderer {
    QuadMeshGenerator::QuadMeshGenerator(const std::shared_ptr<IMeshBuilder>& builder) : IMeshGenerator(builder) {

    }

    void QuadMeshGenerator::reset() {

    }

    std::shared_ptr<IMesh> QuadMeshGenerator::generate() {
        const std::vector<Vertex> vertices {
            {{1.0f,  1.0f, 0.0f},    {1.0f, 0.0f, 0.0f},   {1.0f, 1.0f}},
            {{1.0f, -1.0f, 0.0f},    {0.0f, 1.0f, 0.0f},   {1.0f, 0.0f}},
            {{-1.0f, -1.0f,0.0f},   {0.0f, 0.0f, 1.0f},   {0.0f, 0.0f}},
            {{-1.0f,  1.0f,0.0f},   {1.0f, 1.0f, 0.0f},   {0.0f, 1.0f}}
        };

        const std::vector<u32> indices {
            0, 1, 3,
            1, 2, 3
        };

        builder->append_raw(vertices.data(), vertices.size(), indices.data(), indices.size());

        return builder->build();
    }
}
