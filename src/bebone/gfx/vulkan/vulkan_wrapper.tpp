#ifndef _BEBONE_GFX_VULKAN_VULKAN_WRAPPER_TPP_
#define _BEBONE_GFX_VULKAN_VULKAN_WRAPPER_TPP_

namespace bebone::gfx::vulkan {
    class VulkanDevice;

    class VulkanApi {
        public:
            virtual ~VulkanApi() = default;
            virtual void destroy(VulkanDevice& device) = 0;
    };

    template<class T>
    class VulkanWrapper : public VulkanApi {
        public:
            T backend;
    };
}

#endif
