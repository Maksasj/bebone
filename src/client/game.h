#ifndef _GAME_H_
#define _GAME_H_

#include "utils.h"
#include "client_backend.h"

#include "rendering_world.h"

using namespace bebone::gfx;
using namespace omni::types;

class Game {
    private:
        std::unique_ptr<Window> window;
        std::vector<unsigned int> vertexSpirvCode, fragmentSpirvCode;
        std::unique_ptr<RenderingWorld> renderingWorld;

    public:
        Game() {

        }

        void preinit() {
            RenderingEngine::preinit();
        }

        void init() {
            window = std::make_unique<Window>("Client", 800, 600);
        }

        void load() {
            ShaderCompiler::compile_shader(read_file("assets/vert.glsl").c_str(), EShLangVertex, vertexSpirvCode);
            ShaderCompiler::compile_shader(read_file("assets/frag.glsl").c_str(), EShLangFragment, fragmentSpirvCode);
        }

        void run() {
            VulkanRenderer renderer = VulkanRenderer(*window);

            renderingWorld = std::make_unique<RenderingWorld>(renderer);

            GPUResourceManager resourceManager = renderer.create_gpu_resource_manager();
            GPUResourceSet resourceSet = resourceManager
                .create_resource_set()
                .set_uniform_buffer_resource(0)
                .set_uniform_buffer_resource(1)
                .build();

            PipelineLayout pipelineLayout = renderer
                .create_pipeline_layout_builder()
                .set_constant_range(0, sizeof(GPUHandles))
                .build(resourceManager);

            Pipeline pipeline = renderer.create_pipeline(pipelineLayout, vertexSpirvCode, fragmentSpirvCode);

            struct Camera {
                Mat4f view;
                Mat4f proj;
            };

            Object object = Object{
                .position = Vec3f(0.0f, 0.0f, 2.5f),
                .scale = 0.3f,
                .rotation = Vec3f::splat(0.0f),

                .velocity = Vec3f::splat(0.0f),
                .force = Vec3f::splat(0.0f),
                .mass = 10.0f,

                .renderer = new BoxRenderer(renderer, resourceManager, resourceSet)
            };

            renderingWorld->add_object(&object);

            UniformBuffer<Camera> cameraUbo = resourceManager.create_uniform_buffer<Camera>(resourceSet, 1);

            VulkanCommandBufferPool& commandBufferPool = renderer.get_command_buffer_pool();

            Camera c = {
                Mat4f::translation(Vec3f(0.0f, 0.0f, 0.0f)),
                Mat4f::perspective(1.0472, window->get_aspect(), 0.1f, 10.0f)
            };

            while (!window->closing()) {
                glfwPollEvents();

                uint32_t frame = renderer.get_frame();
                if(frame == 9999) {
                    continue;
                }

                VulkanCommandBuffer& cmd = commandBufferPool.get_command_buffer(frame);

                cameraUbo.get_impl(frame)->set_data(c);

                cmd.begin_record();
                    cmd.begin_render_pass(renderer, frame);
                    cmd.set_viewport(0, 0, window->get_width(), window->get_height());

                    cmd.bind_pipeline(pipeline);
                    resourceSet.bind(cmd, pipelineLayout);

                    cmd.push_constant(pipelineLayout, sizeof(u32), offsetof(GPUHandles, cameraIndex), &cameraUbo.get_handle(frame).index);

                    renderingWorld->record_draw_commands(cmd, pipelineLayout);

                    cmd.end_render_pass();
                cmd.end_record();

                cmd.submit();

                renderer.present(frame);
            }

            vkDeviceWaitIdle(renderer.device->device());

            // Todo since renderer is initilized in this funciton renderingWorld should be delete in this scope
            renderingWorld = nullptr;
        }

        void unload() {

        }

        void cleanup() {
            glfwTerminate();
        }
};

#endif
