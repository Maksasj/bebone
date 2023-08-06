#ifndef _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_H_
#define _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_H_

#include <stdexcept>

#include "../command_buffer.h"

namespace bebone::gfx {
    class VulkanCommandBuffer : public CommandBuffer {
        private:
            core::ArenaAllocator arena;
        protected:

        public:
            VulkanCommandBuffer() : arena(_BEBONE_MEMORY_BYTES_8KB_) {
                
            }

            void begin_record() override {
                VkCommandBufferBeginInfo beginInfo{};
                beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

                if(vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
                    throw std::runtime_error("failed to being recording command buffer");
                }
            }

            void end_record() override {
                if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
                    throw std::runtime_error("failed to end command buffer");
                }
            }

            void* push_bytes(const size_t& size) override {
                return arena.alloc(size);
            }

            void preprocess() override {

            }

            VkCommandBuffer commandBuffer;

            RenderingApi get_api() override {
                return VULKAN;
            }
    };  
}

#endif
