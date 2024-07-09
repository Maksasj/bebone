#include "vulkan_pass.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    // Todo move this outside
    const auto vertex_descriptions = bebone::gfx::VulkanPipelineVertexInputStateTuple {
        .binding_descriptions = {
            { 0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX }
        },
        .attribute_descriptions = {
            { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, position) },
            { 1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, normal) },
            { 2, 0, VK_FORMAT_R32G32_SFLOAT,    offsetof(Vertex, texcoord) },
        }
    };

    // Present pass
    VulkanPresentPass::VulkanPresentPass(
        const std::string& pass_name,
        std::shared_ptr<VulkanDevice>& device,
        std::shared_ptr<VulkanSwapChain>& swap_chain,
        std::shared_ptr<VulkanPipelineManager>& pipeline_manager
    ) : IPresentPass(pass_name), device(device), swap_chain(swap_chain) {
        auto vert_shader_module = device->create_shader_module("#version 450 core\n"
                                                               "#extension GL_EXT_nonuniform_qualifier : enable\n"
                                                               "\n"
                                                               "layout (location = 0) in vec3 position;\n"
                                                               "layout (location = 1) in vec3 normal;\n"
                                                               "layout (location = 2) in vec2 texcoord;\n"
                                                               "\n"
                                                               "layout (location = 0) out vec3 out_normal;\n"
                                                               "layout (location = 1) out vec2 out_texcoord;\n"
                                                               "\n"
                                                               "void main() {\n"
                                                               "    gl_Position = vec4(position, 1.0);\n"
                                                               "\n"
                                                               "    out_normal = normal;\n"
                                                               "    out_texcoord = texcoord;\n"
                                                               "}", VertexShader);

        auto frag_shader_module = device->create_shader_module("#version 450 core\n"
                                                               "#extension GL_EXT_nonuniform_qualifier : enable\n"
                                                               "\n"
                                                               "layout (location = 0) in vec3 normal;\n"
                                                               "layout (location = 1) in vec2 texcoord;\n"
                                                               "\n"
                                                               "layout (location = 0) out vec4 out_color;\n"
                                                               "\n"
                                                               "void main() {\n"
                                                               "   out_color = vec4(texcoord, 1.0, 1.0);\n"
                                                               "}", FragmentShader);

        // Post pipeline
        pipeline = pipeline_manager->create_pipeline(
            device, swap_chain->render_pass, vert_shader_module, frag_shader_module,
            { },
            { { BindlessSampler, 0} },
            { .vertex_input_state = { .vertex_descriptions = vertex_descriptions }, .rasterization_state = { .front_face = VK_FRONT_FACE_COUNTER_CLOCKWISE } }
        );
    }

    void VulkanPresentPass::record(ICommandEncoder* encoder) {
        auto vulkan_encoder = static_cast<VulkanCommandEncoder*>(encoder);

        auto cmd = vulkan_encoder->get_command_buffer();
        const auto& frame = vulkan_encoder->get_frame();

        cmd->begin_render_pass(swap_chain);
            cmd->set_viewport(0, 0, 800, 600);
            cmd->bind_managed_pipeline(pipeline.value(), frame);

            // for (; !render_queue.empty(); render_queue.pop()) {
            //     auto mesh = render_queue.front();
            //     mesh->bind(&encoder);
            //     cmd->draw_indexed(mesh->triangle_count());
            // }
        cmd->end_render_pass();
    }

    void VulkanPresentPass::reset() {

    }

    // Geometry pass
    VulkanGeometryPass::VulkanGeometryPass(const std::string& pass_name) : IGeometryPass(pass_name) {

    }

    void VulkanGeometryPass::record(ICommandEncoder* encoder) {

    }

    void VulkanGeometryPass::reset() {

    }
}
