#ifndef BEBONE_VULKAN_RESULT_H
#define BEBONE_VULKAN_RESULT_H

#include "../gfx_backend.h"

namespace bebone::gfx {
    class VulkanResult {
        private:
            VkResult result;

        public:
            VulkanResult(const VkResult& result);

            static VulkanResult ok();

            bool is_ok();
    };
}

#endif
