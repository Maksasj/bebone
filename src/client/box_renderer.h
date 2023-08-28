#ifndef _BOX_RENDERER_H_
#define _BOX_RENDERER_H_

#include "renderer.h"

const std::vector<Vertex> vertices = {
    {{-1.0f, -1.0f,  1.0}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{ 1.0f, -1.0f,  1.0}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{-1.0f,  1.0f,  1.0}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{ 1.0f,  1.0f,  1.0}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{ 1.0f, -1.0f, -1.0}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{-1.0f,  1.0f, -1.0}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{ 1.0f,  1.0f, -1.0}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}
};

const std::vector<int> indices = {
    2, 6, 7, 2, 3, 7, //Top
    0, 4, 5, 0, 1, 5, //Bottom
    0, 2, 6, 0, 4, 6, //Left
    1, 3, 7, 1, 5, 7, //Right
    0, 2, 3, 0, 1, 3, //Front
    4, 6, 7, 4, 5, 7  //Back
};

class BoxRenderer : public Renderer {
    private:
        std::unique_ptr<VertexBuffer> vertexBuffer;
        std::unique_ptr<IndexBuffer> indexBuffer;

        Transform transform;
        std::unique_ptr<UniformBuffer<Transform>> transformBuffer;

    public: 
        BoxRenderer(VulkanRenderer& renderer, GPUResourceManager& resourceManager, GPUResourceSet& resourceSet) {
            vertexBuffer = std::make_unique<VertexBuffer>(renderer.create_vertex_buffer_impl(vertices));
            indexBuffer = std::make_unique<IndexBuffer>(renderer.create_index_buffer_impl(indices));

            transformBuffer = std::make_unique<UniformBuffer<Transform>>(resourceManager.create_uniform_buffer_impl<Transform>(resourceSet, 0));
        }

        ~BoxRenderer() override {
            vertexBuffer = nullptr;
            indexBuffer = nullptr;
            
            transformBuffer = nullptr;
        }

        void record_draw_commands(VulkanCommandBuffer& cmd, PipelineLayout& pipelineLayout) override {
            const size_t frame = cmd._frameIndex;
            const size_t* transformIndex = &transformBuffer->get_handle(frame).index;

            cmd.bind_vertex_buffer(*vertexBuffer);
            cmd.bind_index_buffer(*indexBuffer);

            // Todo I think we need to move this somewhere else, but still need to think
            transformBuffer->get_impl(cmd._frameIndex)->set_data(transform);

            cmd.push_constant(pipelineLayout, sizeof(u32), offsetof(GPUHandles, transformIndex), transformIndex);
            cmd.draw_indexed(indices.size());
        }

        void calculate_transform(const Vec3f& position, const f32& scale, const Vec3f& rotation) override {
            transform.transform = Mat4f::translation(position);
            transform.scale = Mat4f::scale(scale);
            transform.rotation = trait_bryan_angle_yxz(rotation);
        }
};

#endif
