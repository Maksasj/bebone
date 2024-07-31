#ifndef _BEBONE_RENDERER_QUAD_MESH_GENERATOR_H_
#define _BEBONE_RENDERER_QUAD_MESH_GENERATOR_H_

#include "renderer_backend.h"
#include "mesh/imesh_generator.h"

namespace bebone::renderer {
    class QuadMeshGenerator : public IMeshGenerator<Vertex> {
        private:
            f32 quad_width;
            f32 quad_height;

        public:
            QuadMeshGenerator(const f32& width, const f32& height);

            void set_width(const f32& width);
            void set_height(const f32& height);

            f32 get_width() const;
            f32 get_height() const;

            std::shared_ptr<IMesh> generate(const std::shared_ptr<IMeshBuilder<Vertex>>& builder) override;
    };

}

#endif
