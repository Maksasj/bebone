#ifndef _BEBONE_GFX_VULKAN_VULKAN_FRAME_H_
#define _BEBONE_GFX_VULKAN_VULKAN_FRAME_H_

#include "../gfx_backend.h"

#include "vulkan_command_buffer.h"

namespace bebone::gfx {
    class VulkanFrame {
        private:
            bool _valid;

            VulkanCommandBuffer* commandBuffer;

            VulkanFrame() 
                : frameIndex(0), 
                  _valid(false),
                  commandBuffer(nullptr) {

            }

            VulkanFrame(unsigned int _frameIndex, VulkanCommandBuffer* _commandBuffer) 
                : frameIndex(_frameIndex),
                  _valid(true),
                  commandBuffer(_commandBuffer) {

            }
        
        public:
            unsigned int frameIndex;

            friend class VulkanRenderer;

            const static VulkanFrame invalid;

            const bool& valid() const {
                return _valid;
            }

            VulkanCommandBuffer& get_command_buffer() {
                return *commandBuffer;
            }
    };
}

#endif
