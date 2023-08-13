#ifndef _BEBONE_GFX_VULKAN_BUFFER_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_BUFFER_IMPLEMENTATION_H_

#include <vector>

#include "../../common/common.h"
#include "../buffer_impl.h"
#include "../device_impl.h"

#include "../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::common;

    class VulkanBufferImpl : public BufferImpl {
        private:
            DeviceImpl& device;
            VkBuffer buffer;
            VkDeviceMemory bufferMemory;

            const size_t _size;

        public:
            VulkanBufferImpl(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, DeviceImpl& device) : device(device), _size(static_cast<size_t>(size)) {
                VkBufferCreateInfo bufferInfo{};
                bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
                bufferInfo.size = size;
                bufferInfo.usage = usage;
                bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

                if (vkCreateBuffer(device.device(), &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create vulkan buffer!");
                }

                VkMemoryRequirements memRequirements;
                vkGetBufferMemoryRequirements(device.device(), buffer, &memRequirements);

                VkMemoryAllocateInfo allocInfo{};
                allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
                allocInfo.allocationSize = memRequirements.size;
                allocInfo.memoryTypeIndex = device.findMemoryType(memRequirements.memoryTypeBits, properties);

                if (vkAllocateMemory(device.device(), &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
                    throw std::runtime_error("failed to allocate vulkan buffer memory!");
                }

                vkBindBufferMemory(device.device(), buffer, bufferMemory, 0);
            }

            ~VulkanBufferImpl() {
                vkDestroyBuffer(device.device(), buffer, nullptr);
                vkFreeMemory(device.device(), bufferMemory, nullptr);
            }

            VkBuffer get_buffer() const {
                return buffer;
            }

            size_t get_size() override {
                return _size;
            }

            DeviceImpl& get_device() {
                return device;
            }

            VkDeviceMemory get_buffer_memory() const {
                return bufferMemory;
            }
    };
}

#endif
