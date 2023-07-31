#include <iostream>
#include <thread>

#include "bebone/bebone.h"

using namespace bebone::gfx;
using namespace bebone::common;

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow* window;

bool stopRenderingThread = false;

void render() {
    glfwMakeContextCurrent(window); 

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
 
        glfwSwapBuffers(window);
    }

    vao.terminate();
    vbo.terminate();
    ebo.terminate();
    shader.terminate();

    glfwMakeContextCurrent(NULL);
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    window = glfwCreateWindow(800, 600, "Client", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwMakeContextCurrent(NULL);

    std::thread renderingThread(render);

    while(true) {
        processInput(window);

        glfwPollEvents();
        if(glfwWindowShouldClose(window)) {
            break;
        }
    };

    stopRenderingThread = true;

    std::cout << "Starting joining !\n";

    if(renderingThread.joinable()) {
        std::cout << "Joining !\n";

        renderingThread.join();

        std::cout << "Joined !\n";
    }

    std::cout << "Stopped !\n";

    glfwMakeContextCurrent(window);
    glfwTerminate();

    return 0;
}
