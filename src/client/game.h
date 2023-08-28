#ifndef _GAME_H_
#define _GAME_H_

#include "utils.h"
#include "client_backend.h"

#include "camera.h"
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

            Camera mainCamera(resourceManager, resourceSet);
            
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


            Object object1 = Object{
                .position = Vec3f(0.0f, -3.0f, 0.0f),
                .scale = 2.0f,
                .rotation = Vec3f::splat(0.0f),

                .velocity = Vec3f::splat(0.0f),
                .force = Vec3f::splat(0.0f),
                .mass = 10.0f,

                .renderer = new BoxRenderer(renderer, resourceManager, resourceSet)
            };

            renderingWorld->add_object(&object1);


            Object object2 = Object{
                .position = Vec3f(0.0f, 10.0f, 0.0f),
                .scale = 5.0f,
                .rotation = Vec3f::splat(0.0f),

                .velocity = Vec3f::splat(0.0f),
                .force = Vec3f::splat(0.0f),
                .mass = 10.0f,

                .renderer = new BoxRenderer(renderer, resourceManager, resourceSet)
            };

            renderingWorld->add_object(&object2);

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
