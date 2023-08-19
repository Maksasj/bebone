#include <iostream>
#include <vector>
#include <chrono>

#include "bebone/bebone.h"

#if 1
const char *vvvertexShaderSource = 
                                "#version 450 core\n"
                                "#extension GL_EXT_nonuniform_qualifier : enable\n"
                                "layout(set = 0, binding = 0) uniform TransformUniformBufferObject {\n"
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

    /*
    GPUResourceManager resourceManager = renderer.create_gpu_resource_manager();
    
    // Global gpu resource set
    GPUResourceSet resourceSet = resourceManager
        .create_texture_resource(0)
        .create_uniform_buffer_resource(1, sizeof(float))
        .create_uniform_buffer_resource(2, sizeof(float))
        .build();

    PipelineLayout pipelineLayout = renderer.create_pipeline_layout_builder()
        .bind_resource_set(resourceSet)
        .build();

    VulkanPipeline pipeline = renderer.create_pipeline(pipelineLayout, vertexSpirvCode, fragmentSpirvCode);

    UniformBuffer<float> uniformBuffer1 = resourceManager.create_uniform_buffer<float>(resorceSet, 1);
    UniformBuffer<float> uniformBuffer2 = resourceManager.create_uniform_buffer<float>(resorceSet, 2);

    for(auto frame : get_frames()) {
        cmd.begin_record();
            cmd.begin_render_pass(*swapChain, frame);
            resourceSet.bind(cmd);

            uniformBuffer1.bind(cmd); // Pushes resource handle
            vertexBuffer.bind(cmd);
            indexBuffer.bind(cmd);
            
            uniformBuffer2.bind(cmd); // Pushes resource handle
            vertexBuffer.bind(cmd);
            indexBuffer.bind(cmd);

            cmd.draw_indexed(indices.size());

            cmd.end_render_pass();
        cmd.end_record();

        cmd.submit();
    }

    while (!window.closing()) {
        glfwPollEvents();

        renderer.present();
    }

    */

    auto globalDescriptorLayout = descriptorPool.create_descriptor_set_layout_bindless();
    auto globalDescriptor = descriptorPool.create_descriptor_bindless(globalDescriptorLayout);

    UniformBuffer transformUbo = renderer.create_uniform_buffer(sizeof(float));

    for(int i = 0; i < transformUbo.get_impl_size(); ++i) {
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = static_cast<VulkanUniformBufferImpl*>(transformUbo.get_impl(i))->get_buffer();
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(float);

        VkWriteDescriptorSet descriptorWrite{};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        
        descriptorWrite.dstSet = *globalDescriptor;
        descriptorWrite.dstBinding = 0;
        descriptorWrite.dstArrayElement = 1;
        
        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.pBufferInfo = &bufferInfo;

        descriptorWrite.pImageInfo = nullptr; // Optional
        descriptorWrite.pTexelBufferView = nullptr; // Optional

        vkUpdateDescriptorSets(descriptorPool._device.device(), 1, &descriptorWrite, 0, nullptr);
    }
    
    // descriptorPool.create_descriptor_set_layout();

    PipelineLayoutBuilder pipelineLayoutBuilder = renderer.create_pipeline_layout_builder();
        // pipelineLayoutBuilder.bind_uniform_buffer(0, transformUbo);
        // pipelineLayoutBuilder.bind_texture(texture);
    PipelineLayout pipelineLayout = pipelineLayoutBuilder.build(descriptorPool);

    VulkanPipeline pipeline = renderer.create_pipeline(pipelineLayout, vertexSpirvCode, fragmentSpirvCode);
    
    VertexBuffer vertexBuffer = renderer.create_vertex_buffer(vertices);    
    IndexBuffer indexBuffer = renderer.create_index_buffer(indices);

    unsigned int constant = 1;
    for(size_t i = 0; i < 2; ++i) {
        VulkanCommandBuffer& commandBuffer = commandBufferPool.get_command_buffer(i);
        commandBuffer.begin_record();
            commandBuffer.begin_render_pass(*swapChain, i);
            
            commandBuffer.bind_pipeline(pipeline);
            VulkanCommandBuffer& vkCommandBuffer = static_cast<VulkanCommandBuffer&>(commandBuffer);
            vkCommandBuffer.bind_descriptor_set(pipelineLayout, *globalDescriptor);

            commandBuffer.push_constant(pipelineLayout, sizeof(unsigned int), &constant);

            commandBuffer.bind_vertex_buffer(vertexBuffer);
            commandBuffer.bind_index_buffer(indexBuffer);
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