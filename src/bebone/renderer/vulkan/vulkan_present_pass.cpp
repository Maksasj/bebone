#include "vulkan_present_pass.h"

static const char vulkan_present_pass_vertex_shader_code[] =
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
    "}";

static const char vulkan_present_pass_fragment_shader_code[] =
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
    "}";

const auto vulkan_present_pass_vertex_descriptions = bebone::gfx::VulkanPipelineVertexInputStateTuple {
    .binding_descriptions = {
        { 0, sizeof(bebone::renderer::Vertex), VK_VERTEX_INPUT_RATE_VERTEX }
    },
    .attribute_descriptions = {
        { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(bebone::renderer::Vertex, position) },
        { 1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(bebone::renderer::Vertex, normal) },
        { 2, 0, VK_FORMAT_R32G32_SFLOAT,    offsetof(bebone::renderer::Vertex, texcoord) },
    }
};

namespace bebone::renderer {
    using namespace bebone::gfx;

    // Present pass
    VulkanPresentPass::VulkanPresentPass(
        const std::string& pass_name,
        const Vec2i& viewport
    ) : IPresentPass(pass_name, viewport) {

    }

    void VulkanPresentPass::assemble(IPassAssembler* assember) {
        auto vulkan_assembler = static_cast<VulkanPassAssembler*>(assember);

        auto device = vulkan_assembler->get_device();
        auto swap_chain = vulkan_assembler->get_swap_chain();

        auto program_manager = vulkan_assembler->get_program_manager();
        auto pipeline_manager = program_manager->get_pipeline_manager();

        // Todo
        pipeline_layout = program_manager->get_pipeline_layout();

        auto vert_shader_module = device->create_shader_module(vulkan_present_pass_vertex_shader_code, VertexShader);
        auto frag_shader_module = device->create_shader_module(vulkan_present_pass_fragment_shader_code, FragmentShader);

        // Post pipeline
        auto pipeline = pipeline_manager->create_pipeline(
            device, swap_chain->render_pass, vert_shader_module, frag_shader_module,
            { .vertex_input_state = { .vertex_descriptions = vulkan_present_pass_vertex_descriptions } }
        );

        auto program = program_manager->create_program(pipeline);
        set_program(program);

        auto texture = static_pointer_cast<VulkanHDRTextureResource>(texture_resource);
        texture_handles = texture->get_handles();

        // Todo, move this outside, to assembler
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
            auto& viewport = get_viewport();

            cmd->set_viewport(0, 0, viewport.x, viewport.y);
            program->bind(encoder);

            auto handles = u32(texture_handles[frame]);

            // Todo
            // auto& pipeline = static_pointer_cast<VulkanProgram>(get_program())->get_pipeline();
            cmd->push_constant(pipeline_layout, sizeof(u32), 0, &handles);

            quad_mesh->bind(encoder);
            cmd->draw_indexed(quad_mesh->triangle_count());
        cmd->end_render_pass();
    }

    void VulkanPresentPass::reset() {

    }

    void VulkanPresentPass::resize_viewport(const Vec2i& new_size) {
        // Todo
    }
}
