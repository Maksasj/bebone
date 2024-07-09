#include "vulkan_present_pass.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    // Present pass
    VulkanPresentPass::VulkanPresentPass(const std::string& pass_name) : IPresentPass(pass_name) {

    }

    void VulkanPresentPass::assemble(IPassAssembler* assember) {
        auto vulkan_assembler = static_cast<VulkanPassAssembler*>(assember);

        auto device = vulkan_assembler->get_device();
        auto pipeline_manager = vulkan_assembler->get_pipeline_manager();
        auto swap_chain = vulkan_assembler->get_swap_chain();

        auto vert_shader_module = device->create_shader_module(
            "#version 450 core\n"
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

        auto frag_shader_module = device->create_shader_module(
            "#version 450 core\n"
            "#extension GL_EXT_nonuniform_qualifier : enable\n"
            "\n"
            "layout (location = 0) in vec3 normal;\n"
            "layout (location = 1) in vec2 texcoord;\n"
            "\n"
            "layout (location = 0) out vec4 out_color;\n"
            "\n"
            "layout(binding = 0) uniform sampler2D textures[];\n"
            "\n"
            "layout( push_constant ) uniform Handles {\n"
            "    int texture;\n"
            "} handles;\n"
            "void main() {\n"
            "   out_color = texture(textures[handles.texture], texcoord);\n"
            "}", FragmentShader);

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

        // Post pipeline
        pipeline = pipeline_manager->create_pipeline(
            device, swap_chain->render_pass, vert_shader_module, frag_shader_module,
            { VulkanConstRange::common(sizeof(u32), 0) },
            {
                { BindlessSampler, 0}
            },
            {
                .vertex_input_state = { .vertex_descriptions = vertex_descriptions },
                .rasterization_state = { .front_face = VK_FRONT_FACE_COUNTER_CLOCKWISE }
            }
        );

        auto texture = static_pointer_cast<VulkanTextureResource>(texture_resource)->get_textures();
        texture_handles = pipeline->bind_textures(device, texture, 0);

        auto quad_generator = std::make_shared<QuadMeshGenerator>(std::make_shared<VulkanTriangleMeshBuilder>(*device));
        quad_mesh = quad_generator->generate();

        device->destroy_all(vert_shader_module, frag_shader_module);
        device->collect_garbage();
    }

    void VulkanPresentPass::record(ICommandEncoder* encoder) {
        auto vulkan_encoder = static_cast<VulkanCommandEncoder*>(encoder);

        auto cmd = vulkan_encoder->get_command_buffer();
        const auto& frame = vulkan_encoder->get_frame();

        cmd->begin_render_pass(vulkan_encoder->get_swap_chain());
            cmd->set_viewport(0, 0, 800, 600);
            cmd->bind_managed_pipeline(pipeline.value(), frame);

            auto handles = u32(texture_handles[frame]);
            cmd->push_constant(pipeline->layout, sizeof(u32), 0, &handles);

            quad_mesh->bind(encoder);
            cmd->draw_indexed(quad_mesh->triangle_count());
        cmd->end_render_pass();
    }

    void VulkanPresentPass::reset() {

    }
}
