#ifndef BEXEL_CAMERA_H
#define BEXEL_CAMERA_H

#include "mesh/vertex.h"

namespace bexel {
    class Camera : private core::NonCopyable {
        private:
            i32 m_renderDistance;

            Vec3f m_position;
            Vec3f m_rotation;
            Vec3f m_direction;

            bool m_mouseLocked;

            Mat4f m_viewMatrix;
            Mat4f m_projMatrix;

            Mat4f calculate_view_matrix() const;

    public:
            Camera(const Vec3f& position, const i32& renderDistance);

            void update(shared_ptr<Window>& window);
            void bind(unique_ptr<GLShaderProgram>& shader);

            const Vec3f& get_position() const;
            const i32& get_render_distance() const;
    };
}

#endif
