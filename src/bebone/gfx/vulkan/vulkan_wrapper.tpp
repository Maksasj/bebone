#ifndef _BEBONE_GFX_VULKAN_WRAPPER_TPP_
#define _BEBONE_GFX_VULKAN_WRAPPER_TPP_

namespace bebone::gfx::vulkan {
    class VulkanDevice;

    class VulkanApi {
        private:
            bool destroyed = false;

        protected:
            void mark_destroyed();

        public:
            virtual ~VulkanApi() = default;

            const bool& is_destroyed() const;
            virtual void destroy(VulkanDevice& device) = 0;
    };

    template<class T>
    class VulkanWrapper : public VulkanApi {
        public:
            T backend;
    };
}

#endif
