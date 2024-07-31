#include "quad_mesh_generator.h"

namespace bebone::renderer {
    QuadMeshGenerator::QuadMeshGenerator(
        const f32& width,
        const f32& height
    ) : quad_width(width), quad_height(height) {

    }

    void QuadMeshGenerator::set_width(const f32& width) {
        this->quad_width = width;
    }

    void QuadMeshGenerator::set_height(const f32& height) {
        this->quad_height = height;
    }

    f32 QuadMeshGenerator::get_width() const {
        return quad_width;
    }

    f32 QuadMeshGenerator::get_height() const {
        return quad_height;
    }

    std::shared_ptr<IMesh> QuadMeshGenerator::generate(const std::shared_ptr<IMeshBuilder<Vertex>>& builder) {
        const std::vector<Vertex> vertices {
            {{ -quad_width, -quad_height, 0.0f}, Vec3f::zero, { 0.0f, 1.0f }},
            {{ -quad_width,  quad_height, 0.0f}, Vec3f::zero, { 0.0f, 0.0f }},
            {{  quad_width,  quad_height, 0.0f}, Vec3f::zero, { 1.0f, 0.0f }},
            {{  quad_width, -quad_height, 0.0f}, Vec3f::zero, { 1.0f, 1.0f }}
        };

        const std::vector<u32> indices {
            0, 2, 1, 0, 3, 2
        };

        // Todo, with builder we need to interface via triangle api, not raw
        builder->append_raw(vertices.data(), vertices.size(), indices.data(), indices.size());

        return builder->build();
    }
}
