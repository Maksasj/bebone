#ifndef _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_H_
#define _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_H_

#include "../command_buffer.h"

namespace bebone::gfx {
    class VulkanCommandBuffer : public CommandBuffer {
        private:
            CommandFactory& _commandFactory;
            core::ArenaAllocator arena;

        protected:
            void* push_iternal(const size_t& size) override {
                return arena.alloc(size);
            }

        public:
            VulkanCommandBuffer(CommandFactory& commandFactory) : _commandFactory(commandFactory), arena(_BEBONE_MEMORY_BYTES_8KB_) {
                
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

            void preprocess() override {

            }

            VkCommandBuffer commandBuffer;
    };  
}

#endif
