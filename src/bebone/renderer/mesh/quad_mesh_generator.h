#ifndef _BEBONE_RENDERER_QUAD_MESH_GENERATOR_H_
#define _BEBONE_RENDERER_QUAD_MESH_GENERATOR_H_

#include "renderer_backend.h"
#include "mesh/imesh_generator.h"

namespace bebone::renderer {
    class QuadMeshGenerator : public IMeshGenerator<Vertex> {
        private:
            f32 quad_width;
            f32 quad_height;

            Vec3f quad_origin;
            Vec3f quad_facing;
            Vec3f quad_up_direction;

            // Precalculated points
            std::array<Vec3f, 4> quad_vertices;

            void recalculate_vertices();

        public:
            QuadMeshGenerator(const f32& width, const f32& height, const Vec3f& facing = Vec3f::forward);

            void set_width(const f32& width);
            void set_height(const f32& height);
            void set_facing(const Vec3f& height);

            f32 get_width() const;
            f32 get_height() const;
            Vec3f get_facing() const;

            std::shared_ptr<IMesh> generate(const std::shared_ptr<IMeshBuilder<Vertex>>& builder) override;
    };

}

#endif
