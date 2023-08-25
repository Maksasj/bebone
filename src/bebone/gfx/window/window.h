#ifndef _BEBONE_GFX_WINDOW_H_
#define _BEBONE_GFX_WINDOW_H_

#include <iostream>
#include <exception>

#include "../../core/core.h"

#include "../gfx_backend.h"

namespace bebone::gfx {
    using namespace core;   

    class Window {
        private:
            GLFWwindow* _window;
            int _width;
            int _height;

        public:
            Window(const Window&) = delete;
            Window &operator=(const Window&) = delete;

            Window(const std::string& title, const int width, const int height) :
                _width(width), _height(height) {

                glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
                glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

                _window = glfwCreateWindow(_width, _height, title.c_str(), NULL, NULL);

                if (_window == NULL) {
                    glfwTerminate();
                    throw std::runtime_error("Failed to create GLFW window");
                }
            }

            ~Window() {
                glfwDestroyWindow(_window);
            }

            GLFWwindow* get_backend() const {
                return _window;
            }

            bool closing() const {
                return glfwWindowShouldClose(_window);
            }

            VkExtent2D get_extend() const {
                return { static_cast<uint32_t>(_width), static_cast<uint32_t>(_height) };
            }

            int get_width() const {
                return _width;
            }

            int get_height() const {
                return _height;
            }

            f32 get_aspect() const {
                return static_cast<f32>(_width) / static_cast<f32>(_height);
            }

            void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface_) {
                if(glfwCreateWindowSurface(instance, _window, nullptr, surface_) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create window surface");
                }
            }
    };
}
#endif

/*
//========================================================================
// Simple multi-window example
// Copyright (c) Camilla Löwy <elmindreda@glfw.org>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    int xpos, ypos, height;
    const char* description;
    GLFWwindow* windows[4];

    if (!glfwInit())
    {
        glfwGetError(&description);
        printf("Error: %s\n", description);
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &xpos, &ypos, NULL, &height);

    for (int i = 0;  i < 4;  i++)
    {
        const int size = height / 5;
        const struct
        {
            float r, g, b;
        } colors[] =
        {
            { 0.95f, 0.32f, 0.11f },
            { 0.50f, 0.80f, 0.16f },
            {   0.f, 0.68f, 0.94f },
            { 0.98f, 0.74f, 0.04f }
        };

        if (i > 0)
            glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_FALSE);

        glfwWindowHint(GLFW_POSITION_X, xpos + size * (1 + (i & 1)));
        glfwWindowHint(GLFW_POSITION_Y, ypos + size * (1 + (i >> 1)));

        windows[i] = glfwCreateWindow(size, size, "Multi-Window Example", NULL, NULL);
        if (!windows[i])
        {
            glfwGetError(&description);
            printf("Error: %s\n", description);
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwSetInputMode(windows[i], GLFW_STICKY_KEYS, GLFW_TRUE);

        glfwMakeContextCurrent(windows[i]);
        gladLoadGL(glfwGetProcAddress);
        glClearColor(colors[i].r, colors[i].g, colors[i].b, 1.f);
    }

    for (;;)
    {
        for (int i = 0;  i < 4;  i++)
        {
            glfwMakeContextCurrent(windows[i]);
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(windows[i]);

            if (glfwWindowShouldClose(windows[i]) ||
                glfwGetKey(windows[i], GLFW_KEY_ESCAPE))
            {
                glfwTerminate();
                exit(EXIT_SUCCESS);
            }
        }

        glfwWaitEvents();
    }
}
*/
