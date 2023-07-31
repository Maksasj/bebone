#include <iostream>
#include <thread>

#include "bebone/bebone.h"

using namespace bebone::gfx;
using namespace bebone::common;

bool stopRenderingThread = false;

void render(Window& window) {
    RenderingEngine::setContext(window);
    RenderingEngine::init();

    GLShader shader;
    
    const std::vector<Vertex> vertices = {
        Vertex{0.5f,  0.5f, 0.0f},
        Vertex{0.5f, -0.5f, 0.0f},
        Vertex{-0.5f, -0.5f, 0.0f},
        Vertex{-0.5f,  0.5f, 0.0f},
    };

    const std::vector<unsigned int> indices = {
        0, 1, 3,
        1, 2, 3
    };

    GLVertexArrayObject vao;
    vao.bind();
    GLVertexBufferObject<Vertex> vbo(vertices);
    GLElementBufferObject<unsigned int> ebo(indices);
    vao.link_attribute(0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    vao.unbind();

    while (!stopRenderingThread) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.activate();

        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
 
        RenderingEngine::swapBuffers(window);
    }

    vao.terminate();
    vbo.terminate();
    ebo.terminate();
    shader.terminate();

    RenderingEngine::terminate();
}

int main() {
    RenderingEngine::preinit();
        
    Window window;

    std::thread renderingThread(render, std::ref(window));

    while(true) {
        glfwPollEvents();

        if(window.closing()) {
            break;
        }
    };

    stopRenderingThread = true;

    if(renderingThread.joinable()) {
        renderingThread.join();
    }

    return 0;
}
