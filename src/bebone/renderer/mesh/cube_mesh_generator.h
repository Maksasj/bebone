#ifndef _BEBONE_RENDERER_CUBE_MESH_GENERATOR_H_
#define _BEBONE_RENDERER_CUBE_MESH_GENERATOR_H_

#include "renderer_backend.h"
#include "quad_mesh_generator.h"

namespace bebone::renderer {
    class CubeMeshGenerator : public IMeshGenerator {
        private:
            QuadMeshGenerator quad_generator;

            f32 cube_width;
            f32 cube_height;
            f32 cube_length;

        public:
            CubeMeshGenerator(const f32& width, const f32& height, const f32& length);

            void set_width(const f32& width);
            void set_height(const f32& height);
            void set_length(const f32& length);

            [[nodiscard]] f32 get_width() const;
            [[nodiscard]] f32 get_height() const;
            [[nodiscard]] f32 get_length() const;

            void append_vertices(const std::shared_ptr<IMeshBuilder>& builder) override;
            std::shared_ptr<IMeshImpl> generate(const std::shared_ptr<IMeshBuilder>& builder) override;
    };
}

#endif
