#include "idebug_camera.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    void IDebugCamera::update_camera_rotation() {
        Vec3f rotation = get_rotation();

        // Todo
        const auto winCenterWidth = static_cast<f32>(window->get_width()) / 2.0f;
        const auto winCenterHeight = static_cast<f32>(window->get_height()) / 2.0f;

        handle_mouse_lock(window);

        if(mouse_locked) {
            glfwSetInputMode(window->get_backend(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

            f64 xPos, yPos;
            glfwGetCursorPos(window->get_backend(), &xPos, &yPos);

            const auto deltaX = floorf(winCenterWidth) - static_cast<f32>(xPos);
            const auto deltaY = floorf(winCenterHeight) - static_cast<f32>(yPos);

            rotation.x += deltaY * 0.005f;
            rotation.y -= deltaX * 0.005f; // If this is confusing just think that we rotate Y axis cause of movement mouse a long X axis, actual this make sense

            glfwSetCursorPos(window->get_backend(), winCenterWidth, winCenterHeight);
        } else
            glfwSetInputMode(window->get_backend(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        const Vec3f direction = {
            cos(rotation.y) * cos(rotation.x),
            sin(rotation.x),
            sin(rotation.y) * cos(rotation.x)
        };

        set_rotation(rotation);
        set_direction(direction);
    }

    void IDebugCamera::update_camera_position() {
        const auto dt = Time::get_delta_time();
        const auto direction = get_direction();

        auto movCamera = Vec3f::zero;

        if (glfwGetKey(window->get_backend(), 'W') == GLFW_PRESS)
            movCamera += Vec3f(1.0f, 0.0f, 1.0f) * direction.normalize();

        if (glfwGetKey(window->get_backend(), 'S') == GLFW_PRESS)
            movCamera -= Vec3f(1.0f, 0.0f, 1.0f) * direction.normalize();

        if (glfwGetKey(window->get_backend(), 'A') == GLFW_PRESS)
            movCamera += Vec3f(direction.z, 0.0f, -direction.x).normalize();

        if (glfwGetKey(window->get_backend(), 'D') == GLFW_PRESS)
            movCamera -= Vec3f(direction.z, 0.0f, -direction.x).normalize();

        if (glfwGetKey(window->get_backend(), GLFW_KEY_SPACE) == GLFW_PRESS)
            movCamera.y += 1.0f;

        if (glfwGetKey(window->get_backend(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            movCamera.y -= 1.0f;

        if (glfwGetKey(window->get_backend(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            apply_position(movCamera * speed * dt * 3);
        else
            apply_position(movCamera * speed * dt);
    }

    void IDebugCamera::update_debug_camera() {
        update_camera_rotation();
        update_camera_position();
    }

    void IDebugCamera::handle_mouse_lock(shared_ptr<Window>& window) {
        const auto winCenterWidth = static_cast<f32>(window->get_width()) / 2.0f;
        const auto winCenterHeight = static_cast<f32>(window->get_height()) / 2.0f;

        bool oldMouseLockState = mouse_locked;
        static auto buttonPressed = false;
        const auto isDebugButtonPressed = (glfwGetKey(window->get_backend(), GLFW_KEY_ENTER) == GLFW_RELEASE);
        mouse_locked = (isDebugButtonPressed && !buttonPressed) ? !mouse_locked : mouse_locked;
        buttonPressed = isDebugButtonPressed;

        if(oldMouseLockState != mouse_locked)
            glfwSetCursorPos(window->get_backend(), winCenterWidth, winCenterHeight);
    }

    IDebugCamera::IDebugCamera(const std::shared_ptr<Window>& window) : IPerspectiveCamera(), window(window), speed(1.0f), mouse_locked(false) {
        window->add_listener([&](WindowPullEventsEvent& event) {
            std::ignore = event;

            update_debug_camera();
        });
    }
}
