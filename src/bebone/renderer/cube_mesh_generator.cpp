#include "cube_mesh_generator.h"

namespace bebone::renderer {
    CubeMeshGenerator::CubeMeshGenerator(const std::shared_ptr<IMeshBuilder<Vertex>>& builder) : IMeshGenerator(builder) {

    }

    void CubeMeshGenerator::reset() {

    }

    std::shared_ptr<IMesh> CubeMeshGenerator::generate() {
        const vector<Vertex> vertices {
            {{ -1.0f, -1.0f,  1.0},   {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
            {{  1.0f, -1.0f,  1.0},   {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
            {{ -1.0f,  1.0f,  1.0},   {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
            {{  1.0f,  1.0f,  1.0},   {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{ -1.0f, -1.0f, -1.0},   {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
            {{  1.0f, -1.0f, -1.0},   {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
            {{ -1.0f,  1.0f, -1.0},   {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
            {{  1.0f,  1.0f, -1.0},   {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}
        };

        const vector<u32> indices {
            2, 6, 7,
            2, 3, 7,
            0, 4, 5,
            0, 1, 5,
            0, 2, 6,
            0, 4, 6,
            1, 3, 7,
            1, 5, 7,
            0, 2, 3,
            0, 1, 3,
            4, 6, 7,
            4, 5, 7
        };

        builder->append_raw(vertices.data(), vertices.size(), indices.data(), indices.size());

        return builder->build();
    }
}
