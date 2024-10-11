#include "vulkan_program_manager.h"

static const char present_vert_src[] =
    "#version 450 core\n"
    "#extension GL_EXT_nonuniform_qualifier : enable\n"

    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 normal;\n"
    "layout (location = 2) in vec2 texcoord;\n"

    "layout (location = 0) out vec3 out_normal;\n"
    "layout (location = 1) out vec2 out_texcoord;\n"

    "void main() {\n"
    "    gl_Position = vec4(position, 1.0);\n"

    "    out_normal = normal;\n"
    "    out_texcoord = texcoord;\n"
    "}";

static const char present_frag_src[] =
    "#version 450 core\n"
    "#extension GL_EXT_nonuniform_qualifier : enable\n"

    "layout (location = 0) in vec3 normal;\n"
    "layout (location = 1) in vec2 texcoord;\n"

    "layout (location = 0) out vec4 out_color;\n"

    "layout(set = 0, binding = 2) uniform sampler2D textures[];\n"

    "layout(std140, push_constant) uniform Handles {\n"
    "    int texture;\n"
    "} handles;\n"

    "void main() {\n"
    "   out_color = texture(textures[handles.texture], texcoord);\n"
    "}";

static const char deferred_g_pass_vert_src[] =
    "#version 450 core\n"
    "#extension GL_EXT_nonuniform_qualifier : enable\n"

    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 normal;\n"
    "layout (location = 2) in vec2 texcoord;\n"

    "layout (location = 0) out vec3 out_position;\n"
    "layout (location = 1) out vec3 out_normal;\n"
    "layout (location = 2) out vec2 out_texcoord;\n"

    "layout(set = 0, binding = 0) uniform CameraUBO {\n"
    "   mat4 matrix;\n"
    "} cameraUBO [];\n"

    "layout( push_constant ) uniform Handles {\n"
    "    mat4 transform;\n"
    "    int camera_handle;\n"
    "} handles;\n"

    "void main() {\n"
    "    mat4 model = handles.transform;\n"
    "    mat4 cam = cameraUBO[handles.camera_handle].matrix;\n"
    "    vec4 final_pos = cam * model * vec4(position, 1.0);\n"

    "    out_position = (model * vec4(position, 1.0)).xyz;\n"
    "    out_normal = normal;\n"
    "    out_texcoord = texcoord;\n"

    "    gl_Position = final_pos;\n"
    "}";

static const char deferred_g_pass_frag_src[] =
    "#version 450 core\n"
    "#extension GL_EXT_nonuniform_qualifier : enable\n"

    "layout (location = 0) in vec3 in_position;\n"
    "layout (location = 1) in vec3 in_normal;\n"
    "layout (location = 2) in vec2 in_texcoord;\n"

    "layout (location = 0) out vec4 out_position;\n"
    "layout (location = 1) out vec4 out_normals;\n"
    "layout (location = 2) out vec4 out_albedo;\n"
    "layout (location = 3) out vec4 out_specular;\n"

    "layout(set = 0, binding = 0) uniform MaterialUBO {\n"
    "   int albedo_handle;\n"
    "   int height_handle;\n"
    "   int metallic_handle;\n"
    "   int roughness_handle;\n"
    "} materialUBO [];\n"

    "layout(std140, push_constant) uniform Handles {\n"
    "    mat4 transform;\n"
    "    int camera_handle;\n"
    "    int material_handle;\n"
    "} handles;\n"

    "layout(set = 0, binding = 2) uniform sampler2D textures[];\n"

    "void main() {\n"
    "   out_position = vec4(in_position, 1.0);\n"
    "   out_normals = vec4((in_normal + vec3(1.0f, 1.0f, 1.0f)) / 2.0f, 1.0);\n"
    "   out_albedo =  vec4(texture(textures[materialUBO[handles.material_handle].albedo_handle], in_texcoord));\n"
    "   out_specular = vec4(texture(textures[materialUBO[handles.material_handle].roughness_handle], in_texcoord));\n"
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
    VulkanProgramManager::VulkanProgramManager(const std::shared_ptr<VulkanDevice>& device) : device(device) {
        pipeline_manager = device->create_pipeline_manager();

        this->cache_source("present_src", present_vert_src, present_frag_src);
        this->cache_source("deferred_g_src", deferred_g_pass_vert_src, deferred_g_pass_frag_src);
    }

    std::shared_ptr<IProgram> VulkanProgramManager::create_program(
        const std::shared_ptr<IPassImpl>& impl,
        const std::string& vertex_shader_code,
        const std::string& fragment_shader_code
    ) {
        auto vert_shader_module = device->create_shader_module(vertex_shader_code, ShaderType::VertexShader);
        auto frag_shader_module = device->create_shader_module(fragment_shader_code, ShaderType::FragmentShader);

        // Create pipeline
        auto render_pass = static_pointer_cast<VulkanPassImpl>(impl)->get_vulkan_pass();

        auto pipeline = pipeline_manager->create_pipeline(
            device, render_pass, vert_shader_module, frag_shader_module,
            { .vertex_input_state = { .vertex_descriptions = vulkan_present_pass_vertex_descriptions } }
        );

        // Delete shader modules and clear memory
        // device->destroy_all(vert_shader_module, frag_shader_module); Todo
        // device->collect_garbage();

        return std::make_shared<VulkanProgram>(pipeline, pipeline_manager->get_pipeline_layout());
    }

    void VulkanProgramManager::bind_texture(std::shared_ptr<VulkanTextureImpl>& texture) {
        texture->handle = pipeline_manager->bind_texture(device, texture->get_texture());
    }

    std::shared_ptr<VulkanPipelineManager> VulkanProgramManager::get_pipeline_manager() const {
        return pipeline_manager;
    }

    std::shared_ptr<VulkanDescriptorSet> VulkanProgramManager::get_descriptor_set() const {
        return pipeline_manager->get_descriptor_set();
    }

    std::shared_ptr<VulkanDescriptorSetLayout> VulkanProgramManager::get_descriptor_set_layout() const {
        return pipeline_manager->get_descriptor_set_layout();
    }

    std::shared_ptr<VulkanPipelineLayout> VulkanProgramManager::get_pipeline_layout() const {
        return pipeline_manager->get_pipeline_layout();
    }
}
