#include <iostream>
#include <fstream>
#include <stdlib.h>

#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
#define OMNI_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

#include "camera.h"

using namespace bebone::gfx;
using namespace bebone::core;

struct Transform {
    Mat4f transform;
    Mat4f scale;
    Mat4f rotation;
};

std::string read_file(const std::string& path);

Mat4f getViewMatrix(Vec3f position, Vec3f direction, Vec3f up);

class Chunk {
    private:
        std::unique_ptr<UniformBuffer<Transform>> transformUBO;
        
        Vec3f position;

        Transform transform;
        size_t indecisesCount;

        std::unique_ptr<VertexBuffer> vertexBuffer;
        std::unique_ptr<IndexBuffer> indexBuffer;

        Chunk() {

        }
    public:
        Chunk(GPUResourceManager& resourceManager, GPUResourceSet& resourceSet, const Vec3f& pos) {
            transformUBO = std::make_unique<UniformBuffer<Transform>>(resourceManager.create_uniform_buffer_impl<Transform>(resourceSet, 0));
        
            position = pos;

            transform = Transform{
                Mat4f::translation(position),
                Mat4f::scale(1.0f),
                Mat4f::identity()
            };
        }

        void generate(VulkanRenderer& renderer) {
            std::vector<Vertex> vertices;
            std::vector<int> indices;

            const std::vector<Vertex> cubeVertices = {
                {{-0.5f, -0.5f,  0.5}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
                {{ 0.5f, -0.5f,  0.5}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
                {{-0.5f,  0.5f,  0.5}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
                {{ 0.5f,  0.5f,  0.5}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
                {{-0.5f, -0.5f, -0.5}, {0.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
                {{ 0.5f, -0.5f, -0.5}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
                {{-0.5f,  0.5f, -0.5}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
                {{ 0.5f,  0.5f, -0.5}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}
            };

            const std::vector<int> cubeIndices = {
                2, 6, 7, 2, 3, 7, //Top
                0, 4, 5, 0, 1, 5, //Bottom
                0, 2, 6, 0, 4, 6, //Left
                1, 3, 7, 1, 5, 7, //Right
                0, 2, 3, 0, 1, 3, //Front
                4, 6, 7, 4, 5, 7  //Back
            };

            int indicesOffset = 0;

            for(int x = 0; x < 64; ++x) {
                for(int y = 0; y < 64; ++y) {
                    for(int z = 0; z < 64; ++z) {
                        int value = rand() % 5;

                        if(value == 1) {
                            std::vector<Vertex> transformedCubeVertices;
                            std::vector<int> transformedCubeIndices;

                            for(auto vertex : cubeVertices) {
                                vertex.pos += Vec3f(x, y, z);
                                transformedCubeVertices.push_back(vertex);
                            }

                            for(auto index : cubeIndices) {
                                transformedCubeIndices.push_back(index + indicesOffset);
                            }

                            indicesOffset += 8;

                            for(const auto& vertex : transformedCubeVertices)
                                vertices.push_back(vertex);

                            for(const auto& index : transformedCubeIndices)
                                indices.push_back(index);
                        }                          
                    }
                }
            }

            indecisesCount = indices.size();

            vertexBuffer = std::make_unique<VertexBuffer>(renderer.create_vertex_buffer_impl(vertices));
            indexBuffer = std::make_unique<IndexBuffer>(renderer.create_index_buffer_impl(indices));
        }

        void render(VulkanFrame& frame, PipelineLayout& pipelineLayout) {
            VulkanCommandBuffer& cmd = frame.get_command_buffer();

            cmd.bind_vertex_buffer(*vertexBuffer);
            cmd.bind_index_buffer(*indexBuffer);

            transformUBO->set_data(frame, transform);

            cmd.push_constant(pipelineLayout, sizeof(u32), offsetof(Handles, transformHandle), &transformUBO->get_handle(frame.frameIndex).index);
            cmd.draw_indexed(indecisesCount);
        }
};

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

int main() {
    RenderingEngine::preinit();

    Window window("2. Vulkan 3d cube example", 800, 600);

    VulkanRenderer renderer = VulkanRenderer(window);
    
    GPUResourceManager resourceManager = renderer.create_gpu_resource_manager();
    GPUResourceSet resourceSet = resourceManager
        .create_resource_set()
        .add_uniform_buffer_resource(0)
        .add_uniform_buffer_resource(1)
        .build();

    PipelineLayout pipelineLayout = renderer
        .create_pipeline_layout_builder()
        .set_constant_range(0, sizeof(Handles))
        .build(resourceManager);

    std::vector<unsigned int> vertexSpirvCode;
    std::vector<unsigned int> fragmentSpirvCode;

    ShaderCompiler::compile_shader(read_file("examples/assets/gfx/vulkan/2_vulkan_3d_cube/vert.glsl").c_str(), EShLangVertex, vertexSpirvCode);
    ShaderCompiler::compile_shader(read_file("examples/assets/gfx/vulkan/2_vulkan_3d_cube/frag.glsl").c_str(), EShLangFragment, fragmentSpirvCode);

    Pipeline pipeline = renderer.create_pipeline(pipelineLayout, vertexSpirvCode, fragmentSpirvCode);

    VulkanCommandBufferPool& commandBufferPool = renderer.get_command_buffer_pool();

    Camera mainCamera(resourceManager, resourceSet);

    std::vector<std::unique_ptr<Chunk>> chunks;

    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
            chunks.emplace_back(std::make_unique<Chunk>(resourceManager, resourceSet, Vec3f(64.0f * i, 0.0f, 64.0f * j)));

    for(auto& chunk : chunks)
        chunk->generate(renderer);

    f32 t = 0.0f;
    while (!window.closing()) {
        glfwPollEvents();

        VulkanFrame frame = renderer.get_frame();

        if(!frame.valid())
            continue;
        
        VulkanCommandBuffer& cmd = frame.get_command_buffer();

        cmd.begin_record();
            cmd.begin_render_pass(renderer, frame.frameIndex);
            cmd.set_viewport(0, 0, window.get_width(), window.get_height());

            cmd.bind_pipeline(pipeline);
            resourceSet.bind(cmd, pipelineLayout);

            mainCamera.calculate_transform(window);
            mainCamera.activate(cmd, pipelineLayout);

            for(auto& chunk : chunks)
                chunk->render(frame, pipelineLayout);

            cmd.end_render_pass();
        cmd.end_record();

        cmd.submit();

        renderer.present(frame);

        printFPS();
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
