#include "camera.h"

namespace bexel {
    Camera::Camera(const Vec3f& position, const i32& renderDistance) : m_ubo(nullptr) {
        m_ubo = make_unique<GLUniformBufferObject>(sizeof(CameraMatrices));

        m_renderDistance = renderDistance;

        m_position = position;
        m_rotation = Vec3f(0.0f, 0.0f, 0.0f);
        m_direction = Vec3f::splat(0.0f);

        m_mouseLocked = true;

        m_viewMatrix = Mat4f::identity();
        m_projMatrix = Mat4f::identity();
    }

    Mat4f Camera::calculate_view_matrix() const {
        const static auto upVector = Vec3f(0.0f, -1.0f, 0.0f);

        const auto w = m_direction.normalize();
        const auto u = w.cross(upVector).normalize();
        const auto v = w.cross(u);

        Mat4f viewMatrix = Mat4f::identity();
        viewMatrix[0 * 4 + 0] = u.x;
        viewMatrix[1 * 4 + 0] = u.y;
        viewMatrix[2 * 4 + 0] = u.z;
        viewMatrix[0 * 4 + 1] = v.x;
        viewMatrix[1 * 4 + 1] = v.y;
        viewMatrix[2 * 4 + 1] = v.z;
        viewMatrix[0 * 4 + 2] = w.x;
        viewMatrix[1 * 4 + 2] = w.y;
        viewMatrix[2 * 4 + 2] = w.z;
        viewMatrix[3 * 4 + 0] = -1.0f * (u).dot(m_position);
        viewMatrix[3 * 4 + 1] = -1.0f * (v).dot(m_position);
        viewMatrix[3 * 4 + 2] = -1.0f * (w).dot(m_position);

        return viewMatrix;
    }

    void Camera::update(shared_ptr<Window>& window) {
        float speed = 0.5f;

        if (glfwGetKey(window->get_backend(), 'W') == GLFW_PRESS)
            m_position += Vec3f(1.0f, 0.0f, 1.0f) * m_direction.normalize() * speed;

        if (glfwGetKey(window->get_backend(), 'S') == GLFW_PRESS)
            m_position -= Vec3f(1.0f, 0.0f, 1.0f) * m_direction.normalize() * speed;

        if (glfwGetKey(window->get_backend(), 'A') == GLFW_PRESS)
            m_position -= Vec3f(m_direction.z, 0.0f, -m_direction.x).normalize() * speed;

        if (glfwGetKey(window->get_backend(), 'D') == GLFW_PRESS)
            m_position += Vec3f(m_direction.z, 0.0f, -m_direction.x).normalize() * speed;

        if (glfwGetKey(window->get_backend(), GLFW_KEY_SPACE) == GLFW_PRESS)
            m_position.y += speed;

        if (glfwGetKey(window->get_backend(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            m_position.y -= speed;

        bool oldMouseLockState = m_mouseLocked;
        static auto buttonPressed = false;
        const auto isDebugButtonPressed = (glfwGetKey(window->get_backend(), GLFW_KEY_ENTER) == GLFW_RELEASE);
        m_mouseLocked = (isDebugButtonPressed && !buttonPressed) ? !m_mouseLocked : m_mouseLocked;
        buttonPressed = isDebugButtonPressed;

        if(oldMouseLockState != m_mouseLocked)
            glfwSetCursorPos(window->get_backend(), window->get_width() / 2.0f, window->get_height() / 2.0f);

        if(m_mouseLocked) {
            glfwSetInputMode(window->get_backend(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

            const f64 centerXPos = window->get_width() / 2.0f;
            const f64 centerYPos = window->get_height() / 2.0f;

            f64 xPos, yPos;
            glfwGetCursorPos(window->get_backend(), &xPos, &yPos);

            const f32 deltaX = floor(centerXPos) - xPos;
            const f32 deltaY = floor(centerYPos) - yPos;

            m_rotation.x += deltaY * 0.005f;
            m_rotation.y += deltaX * 0.005f; // If this is confusing just think that we rotate Y axis cause of movement mouse a long X axis, actual this make sense

            glfwSetCursorPos(window->get_backend(), centerXPos, centerYPos);
        } else
            glfwSetInputMode(window->get_backend(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        m_direction.x = cos(m_rotation.y) * cos(m_rotation.x);
        m_direction.y = sin(m_rotation.x);
        m_direction.z = sin(m_rotation.y) * cos(m_rotation.x);

        m_viewMatrix = calculate_view_matrix();
        m_projMatrix = Mat4f::perspective(1.0472, window->get_aspect(), 0.1f, 2000.0f);
    }

    void Camera::bind(unique_ptr<GLShaderProgram>& shader) {
        m_ubo->bind();
        shader->bind_buffer("Camera", 1, *m_ubo);
        auto cam = static_cast<CameraMatrices*>(m_ubo->map());

        cam->proj = m_projMatrix;
        cam->view = m_viewMatrix;

        m_ubo->unmap();
        m_ubo->unbind();
    }

    const Vec3f& Camera::get_position() const {
        return m_position;
    }

    const i32& Camera::get_render_distance() const {
        return m_renderDistance;
    }
}
