#ifndef _BEBONE_GFX_VULKAN_VULKAN_RESULT_H_
#define _BEBONE_GFX_VULKAN_VULKAN_RESULT_H_

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
