#include "cube_mesh_generator.h"

namespace bebone::renderer {
    CubeMeshGenerator::CubeMeshGenerator(
        const f32& width,
        const f32& height,
        const f32& length
    ) : quad_generator(width, height), cube_width(width), cube_height(height), cube_length(length) {

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

    void CubeMeshGenerator::append_vertices(const std::shared_ptr<IMeshBuilder>& builder) {
        quad_generator.set_width(cube_width);
        quad_generator.set_height(cube_height);
        quad_generator.set_facing(Vec3f::forward);
        quad_generator.set_origin(Vec3f(0.0f, 0.0f, cube_width));
        quad_generator.append_vertices(builder);

        quad_generator.set_width(cube_width);
        quad_generator.set_height(cube_height);
        quad_generator.set_facing(Vec3f::back);
        quad_generator.set_origin(Vec3f(0.0f, 0.0f, -cube_width));
        quad_generator.append_vertices(builder);

        quad_generator.set_width(cube_width);
        quad_generator.set_height(cube_height);
        quad_generator.set_facing(Vec3f::left);
        quad_generator.set_origin(Vec3f(-cube_width, 0.0f, 0.0f));
        quad_generator.append_vertices(builder);

        quad_generator.set_width(cube_width);
        quad_generator.set_height(cube_height);
        quad_generator.set_facing(Vec3f::right);
        quad_generator.set_origin(Vec3f(cube_width, 0.0f, 0.0f));
        quad_generator.append_vertices(builder);

        quad_generator.set_width(cube_width);
        quad_generator.set_height(cube_length);
        quad_generator.set_facing(Vec3f::up);
        quad_generator.set_up(Vec3f::forward);
        quad_generator.set_origin(Vec3f(0.0f, cube_height, 0.0f));
        quad_generator.append_vertices(builder);

        quad_generator.set_width(cube_width);
        quad_generator.set_height(cube_length);
        quad_generator.set_facing(Vec3f::down);
        quad_generator.set_up(Vec3f::forward);
        quad_generator.set_origin(Vec3f(0.0f, -cube_height, 0.0f));
        quad_generator.append_vertices(builder);
    }

    std::shared_ptr<IMesh> CubeMeshGenerator::generate(const std::shared_ptr<IMeshBuilder>& builder) {
        append_vertices(builder);
        return builder->build();
    }
}
