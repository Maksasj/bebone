#ifndef _BEBONE_GFX_VULKAN_WRAPPER_TPP_
#define _BEBONE_GFX_VULKAN_WRAPPER_TPP_

namespace bebone::gfx {
    class VulkanDevice;

    class VulkanApi {
        protected:
            VulkanDevice& device;

        public:
            explicit VulkanApi(VulkanDevice& device);
            virtual ~VulkanApi() = default;
    };

    template<class T>
    class VulkanWrapper : public VulkanApi {
        public:
            T backend;

            explicit VulkanWrapper(VulkanDevice& device) : VulkanApi(device) {

            }
    };
}

#endif
