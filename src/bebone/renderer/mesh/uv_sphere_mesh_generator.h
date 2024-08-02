#ifndef _BEBONE_RENDERER_UV_SPHERE_MESH_GENERATOR_H_
#define _BEBONE_RENDERER_UV_SPHERE_MESH_GENERATOR_H_

#include "renderer_backend.h"
#include "mesh/imesh_generator.h"

namespace bebone::renderer {
    class UVSphereMeshGenerator : public IMeshGenerator {
        private:
            std::vector<Vec3f> sphereVertices;
            std::vector<Vec3f> sphereNormals;
            std::vector<Vec2f> sphereUVs;
            std::vector<unsigned int> sphereIndices;

            f32 radius;
            u32 latitudes;
            u32 longitudes;

        protected:

        public:
            UVSphereMeshGenerator(const f32& radius, const u32& latitudes, const u32& longitudes);

            void generate_sphere_smooth();

            void append_vertices(const std::shared_ptr<IMeshBuilder>& builder) override;
            std::shared_ptr<IMesh> generate(const std::shared_ptr<IMeshBuilder>& builder) override;
    };

}

#endif
