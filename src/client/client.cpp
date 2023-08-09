#include <iostream>
#include <vector>
#include <chrono>

#include "bebone/bebone.h"

const char *vvvertexShaderSource = "#version 450 core\n"
                                "layout(location = 0) in vec2 position;\n"
                                "layout(location = 1) in vec3 color;\n"
                                "layout(location = 0) out vec3 fragColor;\n"
                                "void main() {\n"
                                "   gl_Position = vec4(position, 0.0, 1.0);\n"
                                "   fragColor = color;\n"
                                "}\0";
const char *fffragmentShaderSource = "#version 450 core\n"
                                  "layout (location = 0) out vec4 outColor;\n"
                                  "layout (location = 0) in vec3 fragColor;\n"
                                  "void main() {\n"
                                  "   outColor = vec4(fragColor, 1.0);\n"
                                  "}\n\0";

void sierpinski_triangle(std::vector<bebone::common::Vertex>& vertices, int depth, bebone::common::Vertex pos, float side) {
    if(depth <= 0) {
        vertices.push_back({pos.x, pos.y - side, 1.0, 0.3, 1.0});
        vertices.push_back({pos.x + side, pos.y + side, 1.0, 1.0, 0.3});
        vertices.push_back({pos.x - side, pos.y + side, 0.3, 1.0, 1.0});
    } else {
        const auto halfSide = side / 2.0f;

        sierpinski_triangle(vertices, depth - 1, {pos.x, pos.y - halfSide}, halfSide);
        sierpinski_triangle(vertices, depth - 1, {pos.x + halfSide, pos.y + halfSide}, halfSide);
        sierpinski_triangle(vertices, depth - 1, {pos.x - halfSide, pos.y + halfSide}, halfSide);
    }
}

int main() {
    using namespace bebone::gfx;

    RenderingEngine::preinit();
    
    const std::vector<Vertex> vertices = {
        {-0.5f, -0.5f, 1.0f, 0.0f, 0.0f},
        {0.5f, -0.5f, 0.0f, 1.0f, 0.0f},
        {0.5f, 0.5f, 0.0f, 0.0f, 1.0f},
        {-0.5f, 0.5f, 1.0f, 1.0f, 1.0f}
    };

    const std::vector<int> indices = {
        0, 1, 2, 2, 3, 0
    };

    std::vector<unsigned int> vertexSpirvCode, fragmentSpirvCode;
    ShaderCompiler::compile_shader(vvvertexShaderSource, EShLangVertex, vertexSpirvCode);
    ShaderCompiler::compile_shader(fffragmentShaderSource, EShLangFragment, fragmentSpirvCode);

    Window window("Client");
    Renderer renderer = Renderer::create(VULKAN, window);

    std::shared_ptr<MyEngineSwapChainImpl> swapChain = renderer.get_swap_chain();
    Pipeline pipeline = renderer.create_pipeline(vertexSpirvCode, fragmentSpirvCode);
    
    VertexBuffer vertexBuffer = renderer.create_vertex_buffer(vertices);    
    IndexBuffer indexBuffer = renderer.create_index_buffer(indices);

    CommandBufferPool& commandBufferPool = renderer.get_command_buffer_pool();

    for(size_t i = 0; i < 2; ++i) {
        CommandBuffer& commandBuffer = commandBufferPool.get_command_buffer(i);

        commandBuffer.begin_record();
            commandBuffer.begin_render_pass(*swapChain, i);
            
            commandBuffer.bind_pipeline(pipeline);
            commandBuffer.bind_vertex_buffer(vertexBuffer);
            commandBuffer.bind_index_buffer(indexBuffer);

            // commandBuffer.draw(vertices.size());
            commandBuffer.draw_indexed(indices.size());

            commandBuffer.end_render_pass();
        commandBuffer.end_record();

        commandBuffer.submit();
    }

    while (!window.closing()) {
        glfwPollEvents();

        renderer.present();
    }

    glfwTerminate();

    return 0; 
}