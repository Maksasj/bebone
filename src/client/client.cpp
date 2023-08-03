#include <iostream>
#include <vector>

#include "bebone/bebone.h"

#include "swap_chain.h"
#include "pipeline.h"
#include "model.h"

using namespace bebone::gfx;

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


#include <chrono>

void printFPS() {
    static std::chrono::time_point<std::chrono::steady_clock> oldTime = std::chrono::high_resolution_clock::now();
    static int fps; fps++;

    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - oldTime) >= std::chrono::seconds{ 1 }) {
        oldTime = std::chrono::high_resolution_clock::now();
        std::cout << "FPS: " << fps <<  std::endl;
        fps = 0;
    }
}

void sierpinski_triangle(std::vector<Vertex>& vertices, int depth, Vertex pos, float side) {
    if(depth <= 0) {
        vertices.push_back({pos.x, pos.y - side});
        vertices.push_back({pos.x + side, pos.y + side});
        vertices.push_back({pos.x - side, pos.y + side});
    } else {
        const auto halfSide = side / 2.0f;

        sierpinski_triangle(vertices, depth - 1, {pos.x, pos.y - halfSide}, halfSide);
        sierpinski_triangle(vertices, depth - 1, {pos.x + halfSide, pos.y + halfSide}, halfSide);
        sierpinski_triangle(vertices, depth - 1, {pos.x - halfSide, pos.y + halfSide}, halfSide);
    }
};

int main() {
    RenderingEngine::preinit();

    std::vector<unsigned int> vertexSpirvCode, fragmentSpirvCode;

    ShaderCompiler::compile_shader(vvvertexShaderSource, EShLangVertex, vertexSpirvCode);
    ShaderCompiler::compile_shader(fffragmentShaderSource, EShLangFragment, fragmentSpirvCode);

    Window window("Client");
    MyEngineDevice device(window);

    MyEngineSwapChain swapChain(device, window.get_extend());
    VkPipelineLayout pipelineLayout;

    VkPipelineLayoutCreateInfo pipelineLayouInfo{};
    pipelineLayouInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayouInfo.setLayoutCount = 0;
    pipelineLayouInfo.pSetLayouts = nullptr;
    pipelineLayouInfo.pushConstantRangeCount = 0;
    pipelineLayouInfo.pPushConstantRanges = nullptr;

    if(vkCreatePipelineLayout(device.device(), &pipelineLayouInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create pipeline layout");
    }

    auto pipelineConfig = Pipeline::defaultPipelineConfigInfo(swapChain.width(), swapChain.height());
    pipelineConfig.renderPass = swapChain.getRenderPass();
    pipelineConfig.pipelineLayout = pipelineLayout;
    Pipeline pipeline(device, vertexSpirvCode, fragmentSpirvCode, pipelineConfig);

     std::vector<VkCommandBuffer> commnandBuffers;
    commnandBuffers.resize(swapChain.imageCount());

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;\
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = device.getCommandPool();
    allocInfo.commandBufferCount = static_cast<uint32_t>(commnandBuffers.size());

    if(vkAllocateCommandBuffers(device.device(), &allocInfo, commnandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("Failed to allocate command buffers !");
    }

    #if 1
        const std::vector<Vertex> vertices = {
            {0.0f, -0.5f, 1.0, 0.3, 1.0}, // Top
            {0.5f, 0.5f, 1.0, 1.0, 0.3}, // Right
            {-0.5f, 0.5f, 0.3, 1.0, 1.0}, // Left
        };
    #else
        std::vector<Vertex> vertices;
        sierpinski_triangle(vertices, 5, {0.0, 0.0}, 0.8f);
    #endif

    Model model(device, vertices);

    for(size_t i = 0; i < commnandBuffers.size(); ++i) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if(vkBeginCommandBuffer(commnandBuffers[i], &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to being recording command buffer");
        }

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = swapChain.getRenderPass();
        renderPassInfo.framebuffer = swapChain.getFrameBuffer(i);
        
        renderPassInfo.renderArea.offset = {0, 0};
        renderPassInfo.renderArea.extent = swapChain.getSwapChainExtent();
        
        std::array<VkClearValue, 2> clearValues{};
        clearValues[0].color = {{ 0.1f, 0.1f, 0.1f, 1.0f }};
        clearValues[1].depthStencil = { 1.0f, 0 };
        renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
        renderPassInfo.pClearValues = clearValues.data();

        vkCmdBeginRenderPass(commnandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        pipeline.bind(commnandBuffers[i]);

        model.bind(commnandBuffers[i]);
        model.draw(commnandBuffers[i]);

        vkCmdDraw(commnandBuffers[i], 3, 1, 0, 0);

        vkCmdEndRenderPass(commnandBuffers[i]);
        if (vkEndCommandBuffer(commnandBuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to end command buffer");
        }
    }

    while (!window.closing()) {
        glfwPollEvents();

        uint32_t imageIndex;
        auto result = swapChain.acquireNextImage(&imageIndex);

        if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        result = swapChain.submitCommandBuffers(&commnandBuffers[imageIndex], &imageIndex);
        if(result != VK_SUCCESS) {
            throw std::runtime_error("failed to acquire submit command buffers !\n");
        }

        printFPS();
    }
   
    vkDeviceWaitIdle(device.device());
    vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);

    glfwTerminate();

    return 0; 
}