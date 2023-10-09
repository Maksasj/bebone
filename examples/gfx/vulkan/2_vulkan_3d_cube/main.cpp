#include <iostream>
#include <fstream>

#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
#define OMNI_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

using namespace bebone::gfx;
using namespace bebone::core;

struct Vertex {
    Vec3f pos;
    Vec3f color;
};

const std::vector<Vertex> vertices = {
    {{-1.0, -1.0, -1.0}, {0.0f, 1.0f, 1.0f}},
    {{ 1.0, -1.0, -1.0}, {0.0f, 1.0f, 0.0f}},
    {{ 1.0,  1.0, -1.0}, {0.0f, 0.0f, 1.0f}},
    {{-1.0,  1.0, -1.0}, {0.0f, 0.0f, 0.0f}},
    {{-1.0, -1.0,  1.0}, {1.0f, 1.0f, 1.0f}},
    {{ 1.0, -1.0,  1.0}, {1.0f, 1.0f, 0.0f}},
    {{ 1.0,  1.0,  1.0}, {1.0f, 0.0f, 1.0f}},
    {{-1.0,  1.0,  1.0}, {1.0f, 0.0f, 0.0f}},
};

const std::vector<int> indices = {
    0, 1, 2, 2, 3, 0,
    1, 5, 6, 6, 2, 1,
    7, 6, 5, 5, 4, 7,
    4, 0, 3, 3, 7, 4,
    4, 5, 1, 1, 0, 4,
    3, 2, 6, 6, 7, 3
};

struct Handles {
    u32 cameraHandle;
    u32 transformHandle;
};

struct CameraTransform {
    Mat4f view;
    Mat4f proj;
};

struct Transform {
    Mat4f transform;
    Mat4f scale;
    Mat4f rotation;
};

std::string read_file(const std::string& path);

Mat4f getViewMatrix(Vec3f position, Vec3f direction, Vec3f up);

int main() {
    RenderingEngine::preinit();

    Window window("2. Vulkan 3d cube example", 800, 600);

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
            read_file("examples/assets/gfx/vulkan/2_vulkan_3d_cube/vert.glsl"),
            ShaderTypes::VERTEX_SHADER
        ));
        vertexShaderCode = shaderCompiler.compile(ShaderTypes::VERTEX_SHADER);
    }

    {   // Compiling glsl fragment shader code;
        ShaderCompiler shaderCompiler;
        
        shaderCompiler.add_shader_source(ShaderSource(
            read_file("examples/assets/gfx/vulkan/2_vulkan_3d_cube/frag.glsl"),
            ShaderTypes::FRAGMENT_SHADER
        ));
        fragmentShaderCode = shaderCompiler.compile(ShaderTypes::FRAGMENT_SHADER);
    }

    auto pipeline = renderer.create_pipeline(pipelineLayout, vertexShaderCode, fragmentShaderCode);

    // auto vertexBuffer = device.create_buffer(sizeof(Vertex) * vertices.size());

    auto vertexBuffer = VertexBuffer(renderer.create_vertex_buffer_impl(vertices));
    auto indexBuffer = IndexBuffer(renderer.create_index_buffer_impl(indices));

    auto transformUBO = UniformBuffer<Transform>(resourceManager.create_uniform_buffer_impl<Transform>(resourceSet, 0));
    auto cameraUBO = UniformBuffer<CameraTransform>(resourceManager.create_uniform_buffer_impl<CameraTransform>(resourceSet, 1));

    auto cameraTransform = CameraTransform{
        getViewMatrix(Vec3f(0.0f, 0.0f, 10.0f), Vec3f(0.0f, 0.0f, -1.0f), Vec3f(0.0f, -1.0f, 0.0f)),
        Mat4f::perspective(1.0472, window.get_aspect(), 0.1f, 100.0f)
    };

    auto transform = Transform{
        Mat4f::translation(Vec3f::splat(0.0f)),
        Mat4f::scale(1.0f),
        Mat4f::identity()
    };

    f32 t = 0.0f;
    while (!window.closing()) {
        glfwPollEvents();

        auto frame = renderer.get_frame();

        if(!frame.valid())
            continue;

        transform.rotation = trait_bryan_angle_yxz(Vec3f(t * 0.001f, t * 0.001f, 0.0f));
        cameraTransform.proj = Mat4f::perspective(1.0472, window.get_aspect(), 0.1f, 100.0f);
        ++t;

        auto handles = Handles {
            static_cast<u32>(cameraUBO.get_handle(frame.frameIndex).index),
            static_cast<u32>(transformUBO.get_handle(frame.frameIndex).index)
        };
        
        auto& cmd = frame.get_command_buffer();

        cmd.begin_record();
            cmd.begin_render_pass(renderer, frame.frameIndex);
            cmd.set_viewport(0, 0, window.get_width(), window.get_height());

            cmd.bind_pipeline(pipeline);
            resourceSet.bind(cmd, pipelineLayout);

            cmd.bind_vertex_buffer(vertexBuffer);
            cmd.bind_index_buffer(indexBuffer);

            transformUBO.set_data(frame, transform);
            cameraUBO.set_data(frame, cameraTransform);

            cmd.push_constant(pipelineLayout, sizeof(Handles), 0, &handles);

            cmd.draw_indexed(indices.size());

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

Mat4f getViewMatrix(Vec3f position, Vec3f direction, Vec3f up) {
    const Vec3f w = direction.normalize();
    const Vec3f u = w.cross(up).normalize();
    const Vec3f v = w.cross(u);

    Mat4f viewMatrix = Mat4f::identity();
    viewMatrix[0 * 4 + 0] = u.x;
    viewMatrix[1 * 4 + 0] = u.y;
    viewMatrix[2 * 4 + 0] = u.z;
    viewMatrix[0 * 4 + 1] = v.x;
    viewMatrix[1 * 4 + 1] = v.y;
    viewMatrix[2 * 4 + 1] = v.z;
    viewMatrix[0 * 4 + 2] = w.x;
    viewMatrix[1 * 4 + 2] = w.y;
    viewMatrix[2 * 4 + 2] = w.z;
    viewMatrix[3 * 4 + 0] = -1.0f * (u).dot(position);
    viewMatrix[3 * 4 + 1] = -1.0f * (v).dot(position);
    viewMatrix[3 * 4 + 2] = -1.0f * (w).dot(position);

    return viewMatrix;
}
