#include "quad_mesh_generator.h"

namespace bebone::renderer {
    QuadMeshGenerator::QuadMeshGenerator(const std::shared_ptr<IMeshBuilder<Vertex>>& builder) : IMeshGenerator(builder) {

    }

    void QuadMeshGenerator::reset() {

    }

    std::shared_ptr<IMesh> QuadMeshGenerator::generate() {
        const std::vector<Vertex> vertices {
            {{ -1.0f, -1.0f, 0.0f}, Vec3f::zero, {1.0f, 1.0f}},
            {{ -1.0f,  1.0f, 0.0f}, Vec3f::zero, {1.0f, 0.0f}},
            {{ 1.0f,  1.0f, 0.0f},  Vec3f::zero, {0.0f, 0.0f}},
            {{ 1.0f, -1.0f, 0.0f},  Vec3f::zero, {0.0f, 1.0f}}
        };

        const std::vector<u32> indices {
            0, 2, 1, 0, 3, 2
        };

        builder->append_raw(vertices.data(), vertices.size(), indices.data(), indices.size());

        return builder->build();
    }
}
