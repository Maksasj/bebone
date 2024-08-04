#ifndef _BEBONE_RENDERER_VULKAN_COMMAND_ENCODER_H_
#define _BEBONE_RENDERER_VULKAN_COMMAND_ENCODER_H_

#include "icommand_encoder.h"

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
                const size_t& frame);

            void set_viewport(const Vec2i& viewport) override;
            void bind_program(const std::shared_ptr<IProgram>& program) override;

            std::shared_ptr<VulkanDevice>& get_device();
            std::shared_ptr<VulkanSwapChain>& get_swap_chain();

            std::shared_ptr<VulkanCommandBuffer>& get_command_buffer();
            [[nodiscard]] const size_t& get_frame() const;
    };
}
#endif
