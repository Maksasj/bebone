#include <iostream>
#include <fstream>

#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
#define OMNI_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

#include "camera.h"
#include "handles.h"
#include "chunk.h"
#include "world.h"

using namespace bebone::gfx;
using namespace bebone::core;

std::string read_file(const std::string& path);

int main() {
    RenderingEngine::preinit();

    Window window("2. Vulkan voxel example", 800, 600);

    auto renderer = VulkanRenderer(window);
    
    auto resourceManager = renderer.create_gpu_resource_manager();
    auto resourceSet = resourceManager
        .create_resource_set()
        .add_uniform_buffer_resource(0)
        .add_uniform_buffer_resource(1)
        .build();

    auto pipelineLayout = renderer
        .create_pipeline_layout_builder()
        .set_constant_range(0, sizeof(Handles))
        .build(resourceManager);

    ShaderCode vertexShaderCode(ShaderTypes::VERTEX_SHADER);
    ShaderCode fragmentShaderCode(ShaderTypes::FRAGMENT_SHADER);

    {   // Compiling glsl vertex shader code;
        ShaderCompiler shaderCompiler;
        
        shaderCompiler.add_shader_source(ShaderSource(
            read_file("examples/assets/gfx/vulkan/3_vulkan_voxel/vert.glsl"),
            ShaderTypes::VERTEX_SHADER
        ));
        vertexShaderCode = shaderCompiler.compile(ShaderTypes::VERTEX_SHADER);
    }

    {   // Compiling glsl fragment shader code;
        ShaderCompiler shaderCompiler;
        
        shaderCompiler.add_shader_source(ShaderSource(
            read_file("examples/assets/gfx/vulkan/3_vulkan_voxel/frag.glsl"),
            ShaderTypes::FRAGMENT_SHADER
        ));
        fragmentShaderCode = shaderCompiler.compile(ShaderTypes::FRAGMENT_SHADER);
    }

    auto pipeline = renderer.create_pipeline(pipelineLayout, vertexShaderCode, fragmentShaderCode);

    Camera mainCamera(resourceManager, resourceSet);
    World world;

    while (!window.closing()) {
        glfwPollEvents();

        mainCamera.update(window);
        world.update(renderer, resourceManager, resourceSet, mainCamera);

        auto frame = renderer.get_frame();

        if(!frame.valid())
            continue;
        
        auto& cmd = frame.get_command_buffer();

        cmd.begin_record();
            cmd.begin_render_pass(renderer, frame.frameIndex);
            cmd.set_viewport(0, 0, window.get_width(), window.get_height());

            cmd.bind_pipeline(pipeline);
            resourceSet.bind(cmd, pipelineLayout);

            mainCamera.bind(cmd, pipelineLayout);

            world.render(frame, pipelineLayout);

            cmd.end_render_pass();
        cmd.end_record();

        cmd.submit();
        renderer.present(frame);
    }

    vkDeviceWaitIdle(renderer.device->device());

    glfwTerminate();

    return 0;
}

std::string read_file(const std::string& path) {
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}
