#ifndef _BEBONE_RENDERER_CUBE_MESH_GENERATOR_H_
#define _BEBONE_RENDERER_CUBE_MESH_GENERATOR_H_

#include "renderer_backend.h"
#include "imesh_generator.h"

namespace bebone::renderer {
    class CubeMeshGenerator : public IMeshGenerator<Vertex> {
        private:
            f32 cube_width;
            f32 cube_height;
            f32 cube_length;

        public:
            CubeMeshGenerator(const f32& width, const f32& height, const f32& length);

            void set_width(const f32& width);
            void set_height(const f32& height);
            void set_length(const f32& length);

            f32 get_width() const;
            f32 get_height() const;
            f32 get_length() const;

            std::shared_ptr<IMesh> generate(const std::shared_ptr<IMeshBuilder<Vertex>>& builder) override;
    };
}

#endif
