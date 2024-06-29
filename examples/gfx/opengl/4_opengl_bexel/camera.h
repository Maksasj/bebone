#ifndef BEXEL_CAMERA_H
#define BEXEL_CAMERA_H

#include "mesh/vertex.h"

namespace bexel {
    class Camera : private core::NonCopyable {
        private:
            i32 render_distance;

            Vec3f position;
            Vec3f rotation;
            Vec3f direction;

            bool mouse_locked;

            Mat4f view_matrix;
            Mat4f proj_matrix;

            Mat4f calculate_view_matrix() const;

    public:
            Camera(const Vec3f& position, const i32& render_distance);

            void update(shared_ptr<Window>& window);
            void bind(unique_ptr<GLShaderProgram>& shader);

            const Vec3f& get_position() const;
            const i32& get_render_distance() const;
    };
}

#endif
