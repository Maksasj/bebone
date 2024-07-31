#include "cube_mesh_generator.h"

namespace bebone::renderer {
    CubeMeshGenerator::CubeMeshGenerator(
        const f32& width,
        const f32& height,
        const f32& length
    ) : cube_width(width), cube_height(height), cube_length(length) {

    }

    void CubeMeshGenerator::set_width(const f32& width) {
        cube_width = width;
    }

    void CubeMeshGenerator::set_height(const f32& height) {
        cube_height = height;
    }

    void CubeMeshGenerator::set_length(const f32& length) {
        cube_length = length;
    }

    f32 CubeMeshGenerator::get_width() const {
        return cube_width;
    }

    f32 CubeMeshGenerator::get_height() const {
        return cube_height;
    }

    f32 CubeMeshGenerator::get_length() const {
        return cube_length;
    }

    std::shared_ptr<IMesh> CubeMeshGenerator::generate(const std::shared_ptr<IMeshBuilder<Vertex>>& builder) {
        const auto vertices = vector<Vertex> {
            { { -cube_width, -cube_height, cube_length }, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} },
            { { cube_width, -cube_height, cube_length },  {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f} },
            { { cube_width, cube_height, cube_length },   {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f} },
            { { -cube_width, cube_height, cube_length },  {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f} },
            { { -cube_width, -cube_height, -cube_length },  {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f} },
            { { cube_width, -cube_height, -cube_length }, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f} },
            { { cube_width, cube_height, -cube_length },  {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} },
            { { -cube_width, cube_height, -cube_length }, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f} }
        };

        const auto indices = vector<u32> {
            0, 1, 2, 2, 3, 0, 1, 5, 6, 6, 2, 1, 7, 6, 5, 5, 4, 7, 4, 0, 3, 3, 7, 4, 4, 5, 1, 1, 0, 4, 3, 2, 6, 6, 7, 3
        };

        // Todo, with builder we need to interface via triangle api, not raw
        builder->append_raw(vertices.data(), vertices.size(), indices.data(), indices.size());

        return builder->build();
    }
}
