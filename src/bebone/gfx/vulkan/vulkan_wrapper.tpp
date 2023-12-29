#ifndef _BEBONE_GFX_VULKAN_VULKAN_WRAPPER_TPP_
#define _BEBONE_GFX_VULKAN_VULKAN_WRAPPER_TPP_

namespace bebone::gfx::vulkan {
    class VulkanDevice;

    template<class T>
    class VulkanWrapper {
        public:
            T backend;

            virtual void destroy(VulkanDevice& device) = 0;
    };
}

#endif
