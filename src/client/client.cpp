#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "bebone/bebone.h"

GLFWwindow *InitGLFWWindow(int width, int height, const char *title) {
    if (!glfwInit()) {
        std::cerr << "GLFW initialization failed." << std::endl;
        return nullptr;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

    GLFWwindow *window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    glViewport(0, 0, width, height);

    return window;
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    const char *windowTitle = "GLFW Window with Triangle";


    GLFWwindow *window = InitGLFWWindow(screenWidth, screenHeight, windowTitle);
    if (!window) {
        return -1;
    }   

    std::vector<unsigned int> vertexSpirv, fragmentSpirv;

    bebone::gfx::ShaderCompiler::compile_shader(vvvertexShaderSource, EShLangVertex, vertexSpirv);
    bebone::gfx::ShaderCompiler::compile_shader(fffragmentShaderSource, EShLangFragment, fragmentSpirv);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glShaderBinary(1, &vertexShader, GL_SHADER_BINARY_FORMAT_SPIR_V_ARB, vertexSpirv.data(), vertexSpirv.size() * sizeof(unsigned int));
    glSpecializeShaderARB(vertexShader, "main", 0, nullptr, nullptr);
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glShaderBinary(1, &fragmentShader, GL_SHADER_BINARY_FORMAT_SPIR_V_ARB, fragmentSpirv.data(), fragmentSpirv.size() * sizeof(unsigned int));
    glSpecializeShaderARB(fragmentShader, "main", 0, nullptr, nullptr);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint linkStatus;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);
    if (!linkStatus) {
        GLint infoLogLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<GLchar> infoLog(infoLogLength);
        glGetProgramInfoLog(shaderProgram, infoLogLength, nullptr, infoLog.data());
        std::cerr << "Shader program linking error:\n" << infoLog.data() << std::endl;
        glfwTerminate();
        return -1;
    }


    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    glDeleteProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glfwTerminate();

    return 0;
}