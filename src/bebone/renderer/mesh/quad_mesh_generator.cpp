#include "quad_mesh_generator.h"

namespace bebone::renderer {
    using namespace bebone::core;

    QuadMeshGenerator::QuadMeshGenerator(
        const f32& width,
        const f32& height,
        const Vec3f& facing
    ) : quad_width(width), quad_height(height), quad_origin(Vec3f::zero), quad_facing(facing), quad_up_direction(Vec3f::up) {
        recalculate_vertices();
    }

    void QuadMeshGenerator::recalculate_vertices() {
        auto quad_right_direction = Vec3f::cross(quad_facing, quad_up_direction);
        auto quad_new_up_direction = Vec3f::cross(quad_right_direction, quad_facing);

        quad_vertices[0] = quad_origin - quad_right_direction * quad_width - quad_new_up_direction * quad_height;
        quad_vertices[1] = quad_origin - quad_right_direction * quad_width + quad_new_up_direction * quad_height;
        quad_vertices[2] = quad_origin + quad_right_direction * quad_width + quad_new_up_direction * quad_height;
        quad_vertices[3] = quad_origin + quad_right_direction * quad_width - quad_new_up_direction * quad_height;
    }

    void QuadMeshGenerator::set_width(const f32& width) {
        this->quad_width = width;
        recalculate_vertices();
    }

    void QuadMeshGenerator::set_height(const f32& height) {
        this->quad_height = height;
        recalculate_vertices();
    }

    void QuadMeshGenerator::set_facing(const Vec3f& facing) {
        this->quad_facing = facing;
        recalculate_vertices();
    }

    void QuadMeshGenerator::set_origin(const Vec3f &origin) {
        this->quad_origin = origin;
        recalculate_vertices();
    }

    void QuadMeshGenerator::set_up(const Vec3f& up_direction) {
        this->quad_up_direction = up_direction;
        recalculate_vertices();
    }

    f32 QuadMeshGenerator::get_width() const {
        return quad_width;
    }

    f32 QuadMeshGenerator::get_height() const {
        return quad_height;
    }

    Vec3f QuadMeshGenerator::get_facing() const {
        return quad_facing;
    }

    Vec3f QuadMeshGenerator::get_origin() const {
        return quad_origin;
    }

    Vec3f QuadMeshGenerator::get_up() const {
        return quad_up_direction;
    }

    void QuadMeshGenerator::append_vertices(const std::shared_ptr<IMeshBuilder>& builder) {
        // const auto vertices = std::vector<Vertex> {
        //     { quad_vertices[0], quad_facing, { 0.0f, 0.0f } },
        //     { quad_vertices[1], quad_facing, { 0.0f, 1.0f } },
        //     { quad_vertices[2], quad_facing, { 1.0f, 1.0f } },
        //     { quad_vertices[3], quad_facing, { 1.0f, 0.0f } }
        // };

        // static const auto indices = std::array<u32, 6> { 0, 1, 2, 0, 2, 3 };

        const Vertex first[3] = {
            { quad_vertices[0], quad_facing, { 0.0f, 0.0f } },
            { quad_vertices[1], quad_facing, { 0.0f, 1.0f } },
            { quad_vertices[2], quad_facing, { 1.0f, 1.0f } }
        };

        builder->append_triangle(first);

        const Vertex second[3] = {
            { quad_vertices[0], quad_facing, { 0.0f, 0.0f } },
            { quad_vertices[2], quad_facing, { 1.0f, 1.0f } },
            { quad_vertices[3], quad_facing, { 1.0f, 0.0f } }
        };

        builder->append_triangle(second);

        // Todo, with builder we need to interface via triangle api, not raw
        // builder->append_raw(vertices.data(), vertices.size(), indices.data(), indices.size());
    }

    std::shared_ptr<IMeshImpl> QuadMeshGenerator::generate(const std::shared_ptr<IMeshBuilder>& builder) {
        append_vertices(builder);
        return builder->build();
    }
}
