#include "bebone/bebone.h"

using namespace bebone::core;
using namespace bebone::assets;
using namespace bebone::gfx;
using namespace bebone::gfx::vulkan;

struct Vertex {
    Vec3f pos;
    Vec3f color;
    Vec2f texCord;
};

const std::vector<Vertex> vertices {
        {{0.5f,  0.5f, 0.0f},    {1.0f, 0.0f, 0.0f},   {1.0f, 1.0f}},
        {{0.5f, -0.5f, 0.0f},    {0.0f, 1.0f, 0.0f},   {1.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.0f},   {0.0f, 0.0f, 1.0f},   {0.0f, 0.0f}},
        {{-0.5f,  0.5f, 0.0f},   {1.0f, 1.0f, 0.0f},   {0.0f, 1.0f}}
};

const std::vector<u32> indices {
    0, 1, 3, 1, 2, 3
};

// Todo make this nicer
const auto vertexDescriptions = VulkanPipelineVertexInputStateTuple {
    .bindingDescriptions = {
        { 0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX }
    },
    .attributeDescriptions = {
        { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, pos) },
        { 1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, color) },
        { 2, 0, VK_FORMAT_R32G32_SFLOAT, offsetof(Vertex, texCord) }
    }
};

/*
class Texture : NonCopyable {
    shared_ptr<VulkanImage> image;
    shared_ptr<VulkanImageView> view;
    VkSampler sampler;
    VkFormat imageFormat;
    VkImageLayout imageLayout;

    Texture(LveDevice &device, const std::string &filepath);
};
*/

int main() {
    GLFWContext::init();

    auto window = WindowFactory::create_window("2. Vulkan texture example", 800, 600, GfxAPI::VULKAN);

    auto instance = VulkanInstance::create_instance();

    auto device = instance->create_device(window);

    auto commandBufferPool = device->create_command_buffer_pool();
    auto commandBuffers = commandBufferPool->create_command_buffers(device, 3);

    auto swapChain = device->create_swap_chain(window);

    auto descriptorPool = device->create_descriptor_pool();
    auto descriptorSetLayout = device->create_descriptor_set_layouts({
         VulkanDescriptorSetLayoutBinding::bindless_sampler2d(0)
     });

    auto descriptor = descriptorPool->create_descriptor(device, descriptorSetLayout[0]);

    auto vertShaderModule = device->create_shader_module("vert.glsl", ShaderTypes::VERTEX_SHADER);
    auto fragShaderModule = device->create_shader_module("frag.glsl", ShaderTypes::FRAGMENT_SHADER);

    auto pipelineLayout = device->create_pipeline_layout({ descriptorSetLayout }, {});

    auto pipeline = device->create_pipeline(swapChain, pipelineLayout, { vertShaderModule, fragShaderModule }, {
        .pVertexInputState = { .vertexDescriptions = vertexDescriptions }
    });

    auto vertexBuffer = device->create_buffer_memory(sizeof(Vertex) * vertices.size());
    auto indexBuffer = device->create_buffer_memory(sizeof(u32) * indices.size());
    vertexBuffer.memory->upload_data(device, vertices.data(), sizeof(Vertex) * vertices.size());
    indexBuffer.memory->upload_data(device, indices.data(), sizeof(u32) * indices.size());

    // Creating texture start
    auto raw = Image<ColorRGBA>::load_from_file("image.png");

    auto image = device->create_image(VK_FORMAT_R32G32B32A32_SFLOAT, { static_cast<uint32_t>(raw->get_width()), static_cast<uint32_t>(raw->get_height()), 1}, {
        .usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT
    });

    VkMemoryRequirements memRequirements;
    vkGetImageMemoryRequirements(device->device(), image->backend, &memRequirements);

    auto imageMemory = device->create_device_memory(memRequirements, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    imageMemory->bind_image_memory(*device, image);

    image->transition_layout(*commandBufferPool, *device, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

    auto size = raw->get_width() * raw->get_height() * sizeof(ColorRGBA);
    auto staging = device->create_buffer_memory(size);
    staging.memory->upload_data(device, raw->data(), size);

    commandBufferPool->copy_buffer_to_image(*device, staging.buffer, image, raw->get_width(), raw->get_height(), 1);

    image->transition_layout(*commandBufferPool, *device, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

    auto sampler = device->create_sampler();

    auto view = device->create_image_view(*image, VK_FORMAT_R32G32B32A32_SFLOAT);
    // Create texture end

    descriptorPool->update_descriptor_set(device, sampler, view, descriptor, 0, 0);

    while (!window->closing()) {
        GLFWContext::poll_events();

        uint32_t frame;
        if(!swapChain->acquire_next_image(device, &frame).is_ok())
            continue;

        auto& cmd = commandBuffers[frame];

        cmd->begin_record()
            .begin_render_pass(swapChain, frame)
            .set_viewport(0, 0, window->get_width(), window->get_height())
            .bind_pipeline(pipeline)
            .bind_descriptor_set(pipelineLayout, descriptor)
            .bind_vertex_buffer(vertexBuffer.buffer)
            .bind_index_buffer(indexBuffer.buffer)
            .draw_indexed(indices.size())
            .end_render_pass()
            .end_record();

        if(!swapChain->submit_command_buffers(device, cmd, &frame).is_ok()) // Todo check if window is resized
            continue;
    }

    device->wait_idle();

    device->destroy_all(commandBuffers); // Todo \/ lets make all tuples also destroyable
    device->destroy_all(vertexBuffer.buffer, indexBuffer.buffer, vertexBuffer.memory, indexBuffer.memory,commandBufferPool);
    device->destroy_all(vertShaderModule,fragShaderModule,pipelineLayout,pipeline, swapChain);

    device->destroy();
    instance->destroy();

    GLFWContext::terminate();

    return 0;
}
