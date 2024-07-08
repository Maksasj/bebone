#ifndef _BEBONE_RENDERER_VULKAN_COMMAND_ENCODER_H_
#define _BEBONE_RENDERER_VULKAN_COMMAND_ENCODER_H_

#include "../icommand_encoder.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanCommandEncoder : public ICommandEncoder {
        private:
            std::shared_ptr<VulkanCommandBuffer> command_buffer;

        public:
            VulkanCommandEncoder(const std::shared_ptr<VulkanCommandBuffer>& command_buffer);

            std::shared_ptr<VulkanCommandBuffer>& get_command_buffer();
    };
}
#endif
