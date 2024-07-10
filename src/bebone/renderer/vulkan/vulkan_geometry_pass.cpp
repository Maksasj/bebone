#include "vulkan_geometry_pass.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    // Present pass
    VulkanGeometryPass::VulkanGeometryPass(const std::string& pass_name) : IGeometryPass(pass_name) {

    }

    void VulkanGeometryPass::assemble(IPassAssembler* assember) {
        auto vulkan_assembler = static_cast<VulkanPassAssembler*>(assember);

        auto device = vulkan_assembler->get_device();
        auto pipeline_manager = vulkan_assembler->get_pipeline_manager();

        render_pass = device->create_render_pass({800, 600}, {
            VulkanAttachmentDesc::color2D({ 800,600 }, { .format = VK_FORMAT_R32G32B32A32_SFLOAT }),
            VulkanAttachmentDesc::depth2D({ 800,600 }, { .format = device->find_depth_format() }),
        });

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
            "void main() {\n"
            "   out_color = vec4(texcoord, 1.0, 1.0);\n"
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
            device, render_pass, vert_shader_module, frag_shader_module,
            { },
            {
                { BindlessSampler, 0 }
            },
            {
                .vertex_input_state = { .vertex_descriptions = vertex_descriptions },
                .rasterization_state = { .front_face = VK_FRONT_FACE_COUNTER_CLOCKWISE }
            }
        );

        device->destroy_all(vert_shader_module, frag_shader_module);
        device->collect_garbage();

        // Setting render target
        auto texture = static_pointer_cast<VulkanTextureResource>(texture_resource)->get_textures();
        auto depth = static_pointer_cast<VulkanDepthResource>(depth_resource)->get_textures();

        framebuffers = std::vector<std::shared_ptr<VulkanFramebuffer>> {
            device->create_framebuffer({ texture[0]->view, depth[0]->view }, render_pass, {800, 600}),
            device->create_framebuffer({ texture[1]->view, depth[1]->view }, render_pass, {800, 600}),
            device->create_framebuffer({ texture[2]->view, depth[2]->view }, render_pass, {800, 600})
        };
    }

    void VulkanGeometryPass::record(ICommandEncoder* encoder) {
        auto vulkan_encoder = static_cast<VulkanCommandEncoder*>(encoder);

        auto cmd = vulkan_encoder->get_command_buffer();
        const auto& frame = vulkan_encoder->get_frame();

        cmd->begin_render_pass(framebuffers[frame], render_pass);
        cmd->set_viewport(0, 0, 800, 600);
        cmd->bind_managed_pipeline(pipeline.value(), frame);

        auto& render_queue = get_tasks();

        for (; !render_queue.empty(); render_queue.pop()) {
            auto task = render_queue.front();
            task(encoder);
        }

        cmd->end_render_pass();
     }

    void VulkanGeometryPass::reset() {

    }
}