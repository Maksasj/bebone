#include <iostream>
#include <vector>
#include <chrono>

#include "bebone/bebone.h"

#if 1
const char *vvvertexShaderSource = 
                                "#version 450 core\n"
                                "#extension GL_EXT_nonuniform_qualifier : enable\n"
                                "layout(binding = 0) uniform TransformUniformBufferObject {\n"
                                "   float x;"
                                "} transform[];\n"
                                ""
                                "layout (location = 0) in vec2 position;\n"
                                "layout (location = 1) in vec3 color;\n"
                                "layout (location = 2) in vec2 inTexCoord;\n"

                                "layout (location = 0) out vec3 fragColor;\n"
                                "layout (location = 1) out vec2 fragTexCoord;\n"

                                "layout( push_constant ) uniform Handles {\n"
                                "    uint transformHandle;\n"
                                "} handles;\n"

                                "void main() {\n"
                                "    gl_Position = vec4(position.x + transform[handles.transformHandle].x, position.y, 0.0, 1.0);\n"
                                "    fragColor = color;\n"
                                "    fragTexCoord = inTexCoord;\n"
                                "}\0";
#else
const char *vvvertexShaderSource = "#version 450 core\n"
                                "layout (location = 0) in vec2 position;\n"
                                "layout (location = 1) in vec3 color;\n"
                                "layout (location = 2) in vec2 inTexCoord;\n"

                                "layout (location = 0) out vec3 fragColor;\n"
                                "layout (location = 1) out vec2 fragTexCoord;\n"

                                "layout( push_constant ) uniform Handles {\n"
                                "    uint transformHandle;\n"
                                "} handles;\n"

                                "void main() {\n"
                                "   gl_Position = vec4(position.x, position.y, 0.0, 1.0);\n"
                                "   fragColor = color;\n"
                                "   fragTexCoord = inTexCoord;\n"
                                "}\0";
#endif

#if 0
const char *fffragmentShaderSource = "#version 450 core\n"
                                  "layout (location = 0) out vec4 outColor;\n"
                                  "\n"
                                  "layout (location = 0) in vec3 fragColor;\n"
                                  "layout (location = 1) in vec2 fragTexCoord;\n"
                                  "layout (set = 1, binding = 0) uniform sampler2D texSampler;\n"
                                  "void main() {\n"
                                  "   outColor = texture(texSampler, fragTexCoord);\n"
                                  "}\n\0";
#else 
const char *fffragmentShaderSource = "#version 450 core\n"
                                "layout (location = 0) out vec4 outColor;\n"
                                "layout (location = 0) in vec3 fragColor;\n"
                                "layout (location = 1) in vec2 fragTexCoord;\n"
                                    
                                "layout( push_constant ) uniform Handles {\n"
                                "    uint transformHandle;\n"
                                "} handles;\n"

                                "void main() {\n"
                                "   outColor = vec4(fragColor, 1.0);\n"
                                "}\n\0";
#endif

using namespace bebone::gfx;

const std::vector<Vertex> vertices = {
    {-0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f},
    {0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
    {0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
    {-0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f}
};

const std::vector<int> indices = {
    0, 1, 2, 2, 3, 0
};

int main() {
    RenderingEngine::preinit();

    std::vector<unsigned int> vertexSpirvCode, fragmentSpirvCode;
    ShaderCompiler::compile_shader(vvvertexShaderSource, EShLangVertex, vertexSpirvCode);
    ShaderCompiler::compile_shader(fffragmentShaderSource, EShLangFragment, fragmentSpirvCode);

    Window window("Client");
    VulkanRenderer renderer = VulkanRenderer(window);

    std::shared_ptr<MyEngineSwapChainImpl> swapChain = renderer.get_swap_chain();

    VulkanCommandBufferPool& commandBufferPool = renderer.get_command_buffer_pool();
    VulkanDescriptorPool descriptorPool = renderer.create_descriptor_pool();

    GPUResourceManager resourceManager = renderer.create_gpu_resource_manager();
    GPUResourceSet resourceSet = resourceManager
        .create_resource_set()
        .set_uniform_buffer_resource(0, sizeof(float))
        .build();

    UniformBuffer<float> transformUbo = resourceManager.create_uniform_buffer<float>(resourceSet, 0);

    PipelineLayout pipelineLayout = renderer
        .create_pipeline_layout_builder()
        .set_constant_range(0, sizeof(unsigned int))
        .build(resourceManager);

    VulkanPipeline pipeline = renderer.create_pipeline(pipelineLayout, vertexSpirvCode, fragmentSpirvCode);
    
    VertexBuffer vertexBuffer = renderer.create_vertex_buffer(vertices);    
    IndexBuffer indexBuffer = renderer.create_index_buffer(indices);

    for(size_t i = 0; i < 2; ++i) {
        VulkanCommandBuffer& cmd = commandBufferPool.get_command_buffer(i);
        cmd.begin_record();
            cmd.begin_render_pass(*swapChain, i);
            
            cmd.bind_pipeline(pipeline);
            resourceSet.bind(cmd, pipelineLayout);

            GPUResourceHandle uboHandle = transformUbo.get_handle(i);

            // UniformBufferHandle uboHandle = transformUbo.get_handle(i);

            cmd.push_constant(pipelineLayout, sizeof(unsigned int), &uboHandle.index);

            cmd.bind_vertex_buffer(vertexBuffer);
            cmd.bind_index_buffer(indexBuffer);
            cmd.draw_indexed(indices.size());

            cmd.end_render_pass();
        cmd.end_record();

        cmd.submit();
    }

    while (!window.closing()) {
        glfwPollEvents();

        renderer.present();
    }

    glfwTerminate();

    return 0; 
}