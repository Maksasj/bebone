#ifndef _BEBONE_RENDERER_UV_SPHERE_MESH_GENERATOR_H_
#define _BEBONE_RENDERER_UV_SPHERE_MESH_GENERATOR_H_

#include "renderer_backend.h"
#include "mesh/imesh_generator.h"

namespace bebone::renderer {
    class UVSphereMeshGenerator : public IMeshGenerator {
        private:
            f32 sphere_radius;
            u32 sphere_latitudes;
            u32 sphere_longitudes;

            // Precalculated points
            std::vector<Vec3f> sphere_vertices;
            std::vector<Vec3f> sphere_normals;
            std::vector<Vec2f> sphere_texcoord;
            std::vector<unsigned int> sphere_indices;

        protected:
            void recalculate_vertices();

        public:
            UVSphereMeshGenerator(const f32& radius, const u32& latitudes, const u32& longitudes);

            void set_radius(const f32& radius);
            void set_latitudes(const u32& latitudes);
            void set_longitudes(const u32& longitudes);

            [[nodiscard]] f32 get_radius() const;
            [[nodiscard]] u32 get_latitudes() const;
            [[nodiscard]] u32 get_longitudes() const;

            void append_vertices(const std::shared_ptr<IMeshBuilder>& builder) override;
            std::shared_ptr<IMeshImpl> generate(const std::shared_ptr<IMeshBuilder>& builder) override;
    };

}

#endif
