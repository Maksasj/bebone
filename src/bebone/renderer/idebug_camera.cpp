#include "idebug_camera.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    void IDebugCamera::update_camera_rotation() {
        // Todo
        const auto window_center_width = static_cast<f32>(window->get_width()) / 2.0f;
        const auto window_center_height = static_cast<f32>(window->get_height()) / 2.0f;

        handle_mouse_lock(window);

        if(mouse_locked) {
            glfwSetInputMode(window->get_backend(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

            f64 x_pos, y_pos;
            glfwGetCursorPos(window->get_backend(), &x_pos, &y_pos);

            const auto delta_x = floorf(window_center_width) - static_cast<f32>(x_pos);
            const auto delta_y = floorf(window_center_height) - static_cast<f32>(y_pos);

            cam_rotation.x += delta_y * 0.005f;
            cam_rotation.y -= delta_x * 0.005f; // If this is confusing just think that we rotate Y axis cause of movement mouse a long X axis, actual this make sense

            glfwSetCursorPos(window->get_backend(), window_center_width, window_center_height);
        } else
            glfwSetInputMode(window->get_backend(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        const Vec3f direction = {
            cos(cam_rotation.y) * cos(cam_rotation.x),
            sin(cam_rotation.x),
            sin(cam_rotation.y) * cos(cam_rotation.x)
        };

        set_direction(direction);
    }

    void IDebugCamera::update_camera_position() {
        const auto dt = Time::get_delta_time();
        const auto direction = get_direction();

        auto mov_camera = Vec3f::zero;

        if (glfwGetKey(window->get_backend(), 'W') == GLFW_PRESS)
            mov_camera += Vec3f(1.0f, 0.0f, 1.0f) * direction.normalize();

        if (glfwGetKey(window->get_backend(), 'S') == GLFW_PRESS)
            mov_camera -= Vec3f(1.0f, 0.0f, 1.0f) * direction.normalize();

        if (glfwGetKey(window->get_backend(), 'A') == GLFW_PRESS)
            mov_camera += Vec3f(direction.z, 0.0f, -direction.x).normalize();

        if (glfwGetKey(window->get_backend(), 'D') == GLFW_PRESS)
            mov_camera -= Vec3f(direction.z, 0.0f, -direction.x).normalize();

        if (glfwGetKey(window->get_backend(), GLFW_KEY_SPACE) == GLFW_PRESS)
            mov_camera.y += 1.0f;

        if (glfwGetKey(window->get_backend(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            mov_camera.y -= 1.0f;

        if (glfwGetKey(window->get_backend(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            apply_position(mov_camera * speed * dt * 3);
        else
            apply_position(mov_camera * speed * dt);
    }

    void IDebugCamera::update_debug_camera() {
        update_camera_rotation();
        update_camera_position();

        std::cout << get_position() << "\n";
    }

    void IDebugCamera::handle_mouse_lock(shared_ptr<Window>& window) {
        const auto window_center_width = static_cast<f32>(window->get_width()) / 2.0f;
        const auto window_center_height = static_cast<f32>(window->get_height()) / 2.0f;

        bool old_mouse_lock_state = mouse_locked;
        static auto button_pressed = false;
        const auto is_debug_button_pressed = (glfwGetKey(window->get_backend(), GLFW_KEY_ENTER) == GLFW_RELEASE);
        mouse_locked = (is_debug_button_pressed && !button_pressed) ? !mouse_locked : mouse_locked;
        button_pressed = is_debug_button_pressed;

        if(old_mouse_lock_state != mouse_locked)
            glfwSetCursorPos(window->get_backend(), window_center_width, window_center_height);
    }

    IDebugCamera::IDebugCamera(
        const std::shared_ptr<Window>& window
    ) : IPerspectiveCamera(1.0472f, 0.1f, 100.0f), window(window), speed(1.0f), mouse_locked(false), cam_rotation(Vec3f::zero) {
        window->add_listener([&](WindowPullEventsEvent& event) {
            std::ignore = event;

            update_debug_camera();
        });
    }
}
