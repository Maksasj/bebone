#include <iostream>
#include <fstream>

#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
#define OMNI_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

using namespace bebone::gfx;
using namespace bebone::core;

const std::vector<Vertex> vertices = {
    {{-1.0f, -1.0f,  1.0}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
    {{ 1.0f, -1.0f,  1.0}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{-1.0f,  1.0f,  1.0}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{ 1.0f,  1.0f,  1.0}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0}, {0.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
    {{ 1.0f, -1.0f, -1.0}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{-1.0f,  1.0f, -1.0}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{ 1.0f,  1.0f, -1.0}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}
};

const std::vector<int> indices = {
    2, 6, 7, 2, 3, 7, //Top
    0, 4, 5, 0, 1, 5, //Bottom
    0, 2, 6, 0, 4, 6, //Left
    1, 3, 7, 1, 5, 7, //Right
    0, 2, 3, 0, 1, 3, //Front
    4, 6, 7, 4, 5, 7  //Back
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

int main() {
    RenderingEngine::preinit();

    Window window("Vulkan window", 800, 600);

    VulkanRenderer renderer = VulkanRenderer(window);
    
    GPUResourceManager resourceManager = renderer.create_gpu_resource_manager();
    GPUResourceSet resourceSet = resourceManager
        .create_resource_set()
        .set_uniform_buffer_resource(0)
        .set_uniform_buffer_resource(1)
        .build();

    PipelineLayout pipelineLayout = renderer
        .create_pipeline_layout_builder()
        .set_constant_range(0, sizeof(CameraTransform))
        .build(resourceManager);

    std::vector<unsigned int> vertexSpirvCode;
    std::vector<unsigned int> fragmentSpirvCode;

    ShaderCompiler::compile_shader(read_file("examples/assets/gfx/vulkan/2_vulkan_3d_cube/vert.glsl").c_str(), EShLangVertex, vertexSpirvCode);
    ShaderCompiler::compile_shader(read_file("examples/assets/gfx/vulkan/2_vulkan_3d_cube/frag.glsl").c_str(), EShLangFragment, fragmentSpirvCode);

    Pipeline pipeline = renderer.create_pipeline(pipelineLayout, vertexSpirvCode, fragmentSpirvCode);

    VulkanCommandBufferPool& commandBufferPool = renderer.get_command_buffer_pool();

    VertexBuffer vertexBuffer = VertexBuffer(renderer.create_vertex_buffer_impl(vertices));
    IndexBuffer indexBuffer = IndexBuffer(renderer.create_index_buffer_impl(indices));

    UniformBuffer modelTransformUBO = UniformBuffer<Transform>(resourceManager.create_uniform_buffer_impl<Transform>(resourceSet, 0));
    UniformBuffer cameraUBO = UniformBuffer<CameraTransform>(resourceManager.create_uniform_buffer_impl<CameraTransform>(resourceSet, 1));

    Vec3f cameraPos = Vec3f(0.0f, 0.0f, 10.0f);
    Vec3f cameraDir = Vec3f(0.0f, 0.0f, -1.0f);
    Vec3f cameraRot = Vec3f(0.0f, 0.0f, 0.0f);

    f32 t = 0.0f;

    while (!window.closing()) {
        glfwPollEvents();

        CameraTransform cameraTransform = CameraTransform{
            getViewMatrix(cameraPos, cameraDir, Vec3f(0.0f, -1.0f, 0.0f)),
            Mat4f::perspective(1.0472, window.get_aspect(), 0.1f, 100.0f)
        };

        Transform transform = Transform{
            Mat4f::translation(Vec3f::splat(0.0f)),
            Mat4f::scale(1.0f),
            trait_bryan_angle_yxz(Vec3f(t * 0.001f, t * 0.001f, 0.0f))
        };

        ++t;

        uint32_t frame = renderer.get_frame();
        if(frame == 9999)
            continue;

        VulkanCommandBuffer& cmd = commandBufferPool.get_command_buffer(frame);

        cmd.begin_record();
            cmd.begin_render_pass(renderer, frame);
            cmd.set_viewport(0, 0, window.get_width(), window.get_height());

            cmd.bind_pipeline(pipeline);
            resourceSet.bind(cmd, pipelineLayout);

            cmd.bind_vertex_buffer(vertexBuffer);
            cmd.bind_index_buffer(indexBuffer);

            modelTransformUBO.get_impl(cmd._frameIndex)->set_data(transform);
            cameraUBO.get_impl(cmd._frameIndex)->set_data(cameraTransform);

            Handles handles = Handles{
                static_cast<u32>(cameraUBO.get_handle(frame).index),
                static_cast<u32>(modelTransformUBO.get_handle(frame).index)
            };
            
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