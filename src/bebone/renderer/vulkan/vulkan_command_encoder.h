#ifndef _BEBONE_RENDERER_VULKAN_COMMAND_ENCODER_H_
#define _BEBONE_RENDERER_VULKAN_COMMAND_ENCODER_H_

#include "icommand_encoder.h"
#include "vulkan_pass_impl.h"
#include "vulkan_render_target_impl.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanCommandEncoder : public ICommandEncoder {
        private:
            std::shared_ptr<VulkanDevice> device;
            std::shared_ptr<VulkanSwapChain> swap_chain;

        private:
            std::shared_ptr<VulkanCommandBuffer> command_buffer;
            size_t frame;

        public:
            VulkanCommandEncoder(
                const std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<VulkanSwapChain>& swap_chain,
                const std::shared_ptr<VulkanCommandBuffer>& command_buffer,
                const size_t& frame,
                const std::shared_ptr<IMeshManager>& mesh_manager);

            void begin_render_pass(const std::shared_ptr<IRenderTarget>& render_target, const std::shared_ptr<IPassImpl>& pass) override;
            void end_render_pass() override;
            void set_viewport(const Vec2i& viewport) override;
            void bind_program(const std::shared_ptr<IProgram>& program) override;
            void bind_draw_data(const std::shared_ptr<IProgram>& program, const Transform& transform, const std::shared_ptr<IUniformBuffer>& camera, const MaterialHandle& material) override;
            void bind_draw_data(const std::shared_ptr<IProgram>& program, const std::shared_ptr<IAttachment>& attachment) override;
            void draw_indexed(const MeshHandle& handle) override;

            std::shared_ptr<VulkanDevice>& get_device();
            std::shared_ptr<VulkanSwapChain>& get_swap_chain();

            std::shared_ptr<VulkanCommandBuffer>& get_command_buffer();
            [[nodiscard]] const size_t& get_frame() const;
    };
}
#endif
