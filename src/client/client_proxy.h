#ifndef _CLIENT_INTERFACE_H_
#define _CLIENT_INTERFACE_H_

#include <thread>

#include "utils.h"
#include "client_backend.h"

#include "camera.h"
#include "rendering_world.h"

#include "proxy_interface.h"

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

class ClientProxy : public IProxy {
    private:
        std::unique_ptr<Window> window;
        std::vector<unsigned int> vertexSpirvCode, fragmentSpirvCode;
        std::unique_ptr<RenderingWorld> renderingWorld;
        bool running;

    public:
        ClientProxy() {
            running = true;
        }

        ~ClientProxy() override {

        }

        void preinit() override {
            RenderingEngine::preinit();
        }

        void init() override {
            
        }

        void load() override {
            ShaderCompiler::compile_shader(read_file("assets/vert.glsl").c_str(), EShLangVertex, vertexSpirvCode);
            ShaderCompiler::compile_shader(read_file("assets/frag.glsl").c_str(), EShLangFragment, fragmentSpirvCode);
        }

        void run() override {
            std::vector<Object> objects;

            objects.push_back(Object{
                .position = Vec3f(0.0f, 0.0f, 2.5f),
                .scale = 0.3f,
                .rotation = Vec3f::splat(0.0f),

                .velocity = Vec3f::splat(0.0f),
                .force = Vec3f::splat(0.0f),
                .mass = 10.0f,
            }); 

            objects.push_back(Object{
                .position = Vec3f(0.0f, -25.0f, 0.0f),
                .scale = 15.0f,
                .rotation = Vec3f::splat(0.0f),

                .velocity = Vec3f::splat(0.0f),
                .force = Vec3f::splat(0.0f),
                .mass = 10.0f,
            }); 

            objects.push_back(Object{
                .position = Vec3f(5.0f, 10.0f, 0.0f),
                .scale = 5.0f,
                .rotation = Vec3f(1.7f, 1.0f, 0.3f),

                .velocity = Vec3f::splat(0.0f),
                .force = Vec3f::splat(0.0f),
                .mass = 10.0f,
            }); 

            std::thread physicsThread([&]() {
                f32 dt = 0.0f;
                const Vec3f gravity = Vec3f(0.0f, -9.81f, 0.0f);

                while(running) {
                    auto t_start = std::chrono::high_resolution_clock::now();

                    for(auto& obj : objects) {
                        obj.force += gravity * obj.mass;

                        obj.velocity += obj.force / obj.mass * dt;
                        obj.position += obj.velocity * dt;

                        obj.force = Vec3f::splat(0.0f);
                    }
                    auto t_end = std::chrono::high_resolution_clock::now();
                    dt = std::chrono::duration<f32, std::milli>(t_end-t_start).count();

                    const f32 timeToSlip = omni::types::clamp(16.0f - dt, 0.0f, 16.0f - dt); 
                    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<i64>(timeToSlip)));
                }
            });

            std::thread renderingThread([&]() {
                window = std::make_unique<Window>("Client", 800, 600);
                VulkanRenderer renderer = VulkanRenderer(*window);

                renderingWorld = std::make_unique<RenderingWorld>(renderer);

                GPUResourceManager resourceManager = renderer.create_gpu_resource_manager();
                GPUResourceSet resourceSet = resourceManager
                    .create_resource_set()
                    .add_uniform_buffer_resource(0)
                    .add_uniform_buffer_resource(1)
                    .build();

                PipelineLayout pipelineLayout = renderer
                    .create_pipeline_layout_builder()
                    .set_constant_range(0, sizeof(GPUHandles))
                    .build(resourceManager);

                Pipeline pipeline = renderer.create_pipeline(pipelineLayout, vertexSpirvCode, fragmentSpirvCode);

                Camera mainCamera(resourceManager, resourceSet);

                renderingWorld->add_object(&objects[0], resourceManager, resourceSet);
                renderingWorld->add_object(&objects[1], resourceManager, resourceSet);
                renderingWorld->add_object(&objects[2], resourceManager, resourceSet);

                VulkanCommandBufferPool& commandBufferPool = renderer.get_command_buffer_pool();

                while (!window->closing()) {
                    glfwPollEvents();

                    uint32_t frame = renderer.get_frame();
                    if(frame == 9999)
                        continue;

                    VulkanCommandBuffer& cmd = commandBufferPool.get_command_buffer(frame);

                    cmd.begin_record();
                        cmd.begin_render_pass(renderer, frame);
                        cmd.set_viewport(0, 0, window->get_width(), window->get_height());

                        cmd.bind_pipeline(pipeline);
                        resourceSet.bind(cmd, pipelineLayout);

                        mainCamera.calculate_transform(*window);
                        mainCamera.activate(cmd, pipelineLayout);

                        renderingWorld->record_draw_commands(cmd, pipelineLayout);

                        cmd.end_render_pass();
                    cmd.end_record();

                    cmd.submit();

                    renderer.present(frame);
                }

                running = false;

                vkDeviceWaitIdle(renderer.device->device());

                // Todo since renderer is initilized in this funciton renderingWorld should be delete in this scope
                objects.clear(); // Todo since renderer is stored inside object, it needs to be cleared there
                renderingWorld = nullptr;
            });

            renderingThread.join();
        }

        void unload() override {

        }

        void cleanup() override {
            glfwTerminate();
        }
};

#endif
