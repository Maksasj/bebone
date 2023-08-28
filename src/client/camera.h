#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "client_backend.h"
#include "camera_transform.h"
#include "gpu_handles.h"

using namespace bebone::core;

// Todo should be inherited from base object class
class Camera {
    private:
        std::unique_ptr<UniformBuffer<CameraTransform>> transformBuffer;
        CameraTransform transform;

        Vec3f position;
        Vec3f rotation;
        Vec3f direction;

        bool mouseLocked;

    public:
        Camera(GPUResourceManager& resourceManager, GPUResourceSet& resourceSet) {
            transformBuffer = std::make_unique<UniformBuffer<CameraTransform>>(resourceManager.create_uniform_buffer_impl<CameraTransform>(resourceSet, 1));
        
            position = Vec3f::splat(0.0f);
            rotation = Vec3f(0.0f, 0.0f, 0.0f);

            direction = Vec3f::splat(0.0f);

            mouseLocked = true;
        }

        void calculate_transform(Window& window) {
            if (glfwGetKey(window.get_backend(), 'W') == GLFW_PRESS) {
                position += Vec3f(1.0f, 0.0f, 1.0f) * direction.normalize() * 0.02f;
            }

            if (glfwGetKey(window.get_backend(), 'S') == GLFW_PRESS) {
                position -= Vec3f(1.0f, 0.0f, 1.0f) * direction.normalize() * 0.02f;
            }

            if (glfwGetKey(window.get_backend(), 'A') == GLFW_PRESS) {
                position -= Vec3f(direction.z, 0.0f, -direction.x).normalize() * 0.02f;
            }

            if (glfwGetKey(window.get_backend(), 'D') == GLFW_PRESS) {
                position += Vec3f(direction.z, 0.0f, -direction.x).normalize() * 0.02f;
            }

            if (glfwGetKey(window.get_backend(), GLFW_KEY_SPACE) == GLFW_PRESS)
                position.y -= 0.01f;

            if (glfwGetKey(window.get_backend(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
                position.y += 0.01f;

            bool oldMouseLockState = mouseLocked;
            static bool buttonPressed = false;
            const bool isDebugButtonPressed = (glfwGetKey(window.get_backend(), GLFW_KEY_ENTER) == GLFW_RELEASE);
            mouseLocked = (isDebugButtonPressed && !buttonPressed) ? !mouseLocked : mouseLocked;  
            buttonPressed = !isDebugButtonPressed ? false : true;

            if(oldMouseLockState != mouseLocked) {
                glfwSetCursorPos(window.get_backend(), window.get_width() / 2.0f, window.get_height() / 2.0f);   
            }

            if(mouseLocked == true) {
                glfwSetInputMode(window.get_backend(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

                const f64 centerXPos = window.get_width() / 2.0f;
                const f64 centerYPos = window.get_height() / 2.0f;

                f64 xPos, yPos;
                glfwGetCursorPos(window.get_backend(), &xPos, &yPos);
                
                const f32 deltaX = floor(centerXPos) - xPos;
                const f32 deltaY = floor(centerYPos) - yPos;

                rotation.x -= deltaY * 0.005f;
                rotation.y += deltaX * 0.005f;

                glfwSetCursorPos(window.get_backend(), centerXPos, centerYPos);   
            } else {
                glfwSetInputMode(window.get_backend(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }

            direction.x = cos(rotation.y) * cos(rotation.x);
            direction.y = sin(rotation.x);
            direction.z = sin(rotation.y) * cos(rotation.x);

            transform = CameraTransform{
                // getViewMatrix(position, Vec3f(0.0f, 0.0f, 1.0f) - position, Vec3f(0.0f, -1.0f, 0.0f)),
                getViewMatrix(position, direction, Vec3f(0.0f, -1.0f, 0.0f)),
                Mat4f::perspective(1.0472, window.get_aspect(), 0.1f, 100.0f)
            };
        }

        Mat4f getViewMatrix(Vec3f position, Vec3f direction, Vec3f up) {
            const Vec3f w = direction.normalize();
            const Vec3f u = w.cross(up).normalize();
            const Vec3f v = w.cross(u);

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
            viewMatrix[3 * 4 + 0] = -1.0f * (u).dot(position);
            viewMatrix[3 * 4 + 1] = -1.0f * (v).dot(position);
            viewMatrix[3 * 4 + 2] = -1.0f * (w).dot(position);

            return viewMatrix;
        }

        void activate(VulkanCommandBuffer& cmd, PipelineLayout& pipelineLayout) {
            const size_t frame = cmd._frameIndex;
            const size_t* transformIndex = &transformBuffer->get_handle(frame).index;

            transformBuffer->get_impl(frame)->set_data(transform);
            cmd.push_constant(pipelineLayout, sizeof(u32), offsetof(GPUHandles, cameraIndex), transformIndex);
        }
};

#endif
