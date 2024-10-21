#include "camera.h"

namespace bexel {
    Camera::Camera(const Vec3f& position, const i32& render_distance) {
        this->render_distance = render_distance;

        this->position = position;
        rotation = Vec3f::zero;
        direction = Vec3f::zero;

        mouse_locked = true;

        view_matrix = Mat4f::identity();
        proj_matrix = Mat4f::identity();
    }

    void Camera::update(shared_ptr<Window>& window) {
        const f32 speed = 0.5f;

        if (glfwGetKey(window->get_backend(), 'W') == GLFW_PRESS)
            position += Vec3f(1.0f, 0.0f, 1.0f) * direction.normalize() * speed;

        if (glfwGetKey(window->get_backend(), 'S') == GLFW_PRESS)
            position -= Vec3f(1.0f, 0.0f, 1.0f) * direction.normalize() * speed;

        if (glfwGetKey(window->get_backend(), 'A') == GLFW_PRESS)
            position -= Vec3f(direction.z, 0.0f, -direction.x).normalize() * speed;

        if (glfwGetKey(window->get_backend(), 'D') == GLFW_PRESS)
            position += Vec3f(direction.z, 0.0f, -direction.x).normalize() * speed;

        if (glfwGetKey(window->get_backend(), GLFW_KEY_SPACE) == GLFW_PRESS)
            position.y += speed;

        if (glfwGetKey(window->get_backend(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            position.y -= speed;

        bool old_mouse_lock_state = mouse_locked;
        static auto button_pressed = false;
        const auto is_debug_button_pressed = (glfwGetKey(window->get_backend(), GLFW_KEY_ENTER) == GLFW_RELEASE);
        mouse_locked = (is_debug_button_pressed && !button_pressed) ? !mouse_locked : mouse_locked;
        button_pressed = is_debug_button_pressed;

        if(old_mouse_lock_state != mouse_locked)
            glfwSetCursorPos(window->get_backend(), window->get_width() / 2.0f, window->get_height() / 2.0f);

        if(mouse_locked) {
            glfwSetInputMode(window->get_backend(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

            const f64 center_x_pos = window->get_width() / 2.0f;
            const f64 center_y_pos = window->get_height() / 2.0f;

            f64 x_pos, y_pos;
            glfwGetCursorPos(window->get_backend(), &x_pos, &y_pos);

            const f32 delta_x = floor(center_x_pos) - x_pos;
            const f32 delta_y = floor(center_y_pos) - y_pos;

            rotation.x += delta_y * 0.005f;
            rotation.y += delta_x * 0.005f; // If this is confusing just think that we rotate Y axis cause of movement mouse a long X axis, actual this make sense

            glfwSetCursorPos(window->get_backend(), center_x_pos, center_y_pos);
        } else
            glfwSetInputMode(window->get_backend(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        direction.x = cos(rotation.y) * cos(rotation.x);
        direction.y = sin(rotation.x);
        direction.z = sin(rotation.y) * cos(rotation.x);

        view_matrix = Mat4f::view(position, direction);
        proj_matrix = Mat4f::perspective(1.0472, window->get_aspect(), 0.1f, 2000.0f);
    }

    void Camera::bind(unique_ptr<GLShaderProgram>& shader) {
        shader->set_uniform("proj", proj_matrix);
        shader->set_uniform("view", view_matrix);
    }

    const Vec3f& Camera::get_position() const {
        return position;
    }

    const i32& Camera::get_render_distance() const {
        return render_distance;
    }
}
