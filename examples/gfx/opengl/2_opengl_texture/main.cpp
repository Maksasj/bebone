#include "bebone/bebone.h"

#include <iostream>
#include <vector>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace bebone::gfx::opengl;

std::vector<GLfloat> vertices {
    // positions          // colors           // texture coords
    0.5f,  0.5f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
    0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
};

std::vector<GLuint> indices {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Texture example", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    GLShader vertexShader("examples/assets/gfx/opengl/2_opengl_texture/vertex.shader", GL_VERTEX_SHADER);
    GLShader fragmentShader("examples/assets/gfx/opengl/2_opengl_texture/fragment.shader", GL_FRAGMENT_SHADER);
    GLShaderProgram shaderProgram(vertexShader, fragmentShader);

    vertexShader.destroy();
    fragmentShader.destroy();
    
    GLVertexArrayObject vao;
    vao.bind();

    GLVertexBufferObject vbo(vertices);
    GLElementBufferObject ebo(indices);

    vao.link_attributes(vbo, 0, 3, GL_FLOAT, 8 * (sizeof(float)), (void*)0);
    vao.link_attributes(vbo, 1, 3, GL_FLOAT, 8 * (sizeof(float)), (void*)(3 * sizeof(float)));
    vao.link_attributes(vbo, 2, 2, GL_FLOAT, 8 * (sizeof(float)), (void*)(6 * sizeof(float)));

    vao.unbind();
	vbo.unbind();
	ebo.unbind();

    GLTexture texture("examples/assets/gfx/opengl/2_opengl_texture/awesomeface.png",
        GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    shaderProgram.set_uniform("ourTexture", 0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.enable();

        texture.bind();
        vao.bind();

        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vao.destroy();
    vbo.destroy();
    ebo.destroy();
    shaderProgram.destroy();
    texture.destroy();

    glfwTerminate();
    return 0;
}