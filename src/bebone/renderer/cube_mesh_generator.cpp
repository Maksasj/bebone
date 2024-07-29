#include "cube_mesh_generator.h"

namespace bebone::renderer {
    CubeMeshGenerator::CubeMeshGenerator(const std::shared_ptr<IMeshBuilder<Vertex>>& builder) : IMeshGenerator(builder) {

    }

    void CubeMeshGenerator::reset() {

    }

    std::shared_ptr<IMesh> CubeMeshGenerator::generate() {
        const auto vertices = vector<Vertex> {
            { { -1.0, -1.0, 1.0 }, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} },
            { { 1.0, -1.0, 1.0 },  {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f} },
            { { 1.0, 1.0, 1.0 },   {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f} },
            { { -1.0, 1.0, 1.0 },  {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
            { { -1.0, -1.0, -1.0},  {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f} },
            { { 1.0, -1.0, -1.0 }, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f} },
            { { 1.0, 1.0, -1.0 },  {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} },
            { { -1.0, 1.0, -1.0 }, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} }
        };

        const auto indices = vector<u32> {
            0, 1, 2, 2, 3, 0, 1, 5, 6, 6, 2, 1, 7, 6, 5, 5, 4, 7, 4, 0, 3, 3, 7, 4, 4, 5, 1, 1, 0, 4, 3, 2, 6, 6, 7, 3
        };

        builder->append_raw(vertices.data(), vertices.size(), indices.data(), indices.size());

        return builder->build();
    }
}
