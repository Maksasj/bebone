#include "vulkan_deferred_g_pass.h"

static const char vulkan_deferred_g_pass_vertex_shader_code[] =
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
    "    out_normal = normal;\n"
    "    out_texcoord = texcoord;\n"
    "}";

static const char vulkan_deferred_g_pass_fragment_shader_code[] =
    "#version 450 core\n"
    "#extension GL_EXT_nonuniform_qualifier : enable\n"
    "\n"
    "layout (location = 0) in vec3 normal;\n"
    "layout (location = 1) in vec2 texcoord;\n"
    "\n"
    "layout (location = 0) out vec4 out_position;\n"
    "layout (location = 1) out vec4 out_normals;\n"
    "layout (location = 2) out vec4 out_albedo;\n"
    "layout (location = 3) out vec4 out_specular;\n"
    "\n"
    "void main() {\n"
    "   out_albedo = vec4(texcoord, 1.0, 1.0);\n"
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
    VulkanDeferredGPass::VulkanDeferredGPass(
        const std::string& pass_name,
        const Vec2i& viewport
    ) : IDeferredGPass(pass_name, viewport) {

    }

    void VulkanDeferredGPass::assemble(IPassAssembler* assember) {
        auto vulkan_assembler = static_cast<VulkanPassAssembler*>(assember);

        auto device = vulkan_assembler->get_device();
        auto pipeline_manager = vulkan_assembler->get_pipeline_manager();

        auto viewport = VkExtent2D { static_cast<uint32_t>(get_viewport().x), static_cast<uint32_t>(get_viewport().y) };

        render_pass = device->create_render_pass(viewport, {
            VulkanAttachmentDesc::color2D(viewport, { .format = VK_FORMAT_R32G32B32A32_SFLOAT }), /* position */
            VulkanAttachmentDesc::color2D(viewport, { .format = VK_FORMAT_R32G32B32A32_SFLOAT }), /* normals */
            VulkanAttachmentDesc::color2D(viewport, { .format = VK_FORMAT_R32G32B32A32_SFLOAT }), /* albedo */
            VulkanAttachmentDesc::color2D(viewport, { .format = VK_FORMAT_R32G32B32A32_SFLOAT }), /* specular */
            VulkanAttachmentDesc::depth2D(viewport, { .format = device->find_depth_format() }),   /* depth */
        });

        auto vert_shader_module = device->create_shader_module(vulkan_deferred_g_pass_vertex_shader_code, VertexShader);
        auto frag_shader_module = device->create_shader_module(vulkan_deferred_g_pass_fragment_shader_code, FragmentShader);

        // Post pipeline
        auto pipeline = pipeline_manager->create_pipeline(
            device, render_pass, vert_shader_module, frag_shader_module,
            { },
            { { BindlessSampler, 0 } },
            {
                .vertex_input_state = { .vertex_descriptions = vulkan_present_pass_vertex_descriptions },
                .rasterization_state = { .front_face = VK_FRONT_FACE_COUNTER_CLOCKWISE }
            }
        );

        device->destroy_all(vert_shader_module, frag_shader_module);
        device->collect_garbage();

        // Setting render target
        auto position = static_pointer_cast<VulkanTextureResource>(position_resource)->get_textures();
        auto normals = static_pointer_cast<VulkanTextureResource>(normals_resource)->get_textures();
        auto albedo = static_pointer_cast<VulkanTextureResource>(albedo_resource)->get_textures();
        auto specular = static_pointer_cast<VulkanTextureResource>(specular_resource)->get_textures();

        auto depth = static_pointer_cast<VulkanDepthResource>(depth_resource)->get_textures();

        framebuffers = std::vector<std::shared_ptr<VulkanFramebuffer>> {
            device->create_framebuffer({ position[0]->view, normals[0]->view, albedo[0]->view, specular[0]->view, depth[0]->view }, render_pass, viewport),
            device->create_framebuffer({ position[1]->view, normals[1]->view, albedo[1]->view, specular[1]->view, depth[1]->view }, render_pass, viewport),
            device->create_framebuffer({ position[2]->view, normals[2]->view, albedo[2]->view, specular[2]->view, depth[2]->view }, render_pass, viewport)
        };

        set_program(std::make_shared<VulkanProgram>(pipeline));
    }

    void VulkanDeferredGPass::record(ICommandEncoder* encoder) {
        auto vulkan_encoder = static_cast<VulkanCommandEncoder*>(encoder);

        auto cmd = vulkan_encoder->get_command_buffer();
        const auto& frame = vulkan_encoder->get_frame();

        cmd->begin_render_pass(framebuffers[frame], render_pass);
            cmd->set_viewport(0, 0, viewport.x, viewport.y);
            program->bind(encoder);

            auto& render_queue = get_tasks();

            for (; !render_queue.empty(); render_queue.pop()) {
                auto task = render_queue.front();
                task(encoder);
            }

        cmd->end_render_pass();
     }

    void VulkanDeferredGPass::reset() {

    }
}
