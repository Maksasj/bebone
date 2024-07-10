#ifndef _BEBONE_RENDERER_VULKAN_RESOURCE_FACTORY_H_
#define _BEBONE_RENDERER_VULKAN_RESOURCE_FACTORY_H_

#include "../iresource_factory.h"

#include "vulkan_texture_resource.h"
#include "vulkan_depth_resource.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanResourceFactory : public IResourceFactory {
        private:
            std::shared_ptr<VulkanDevice> device;

        public:
            VulkanResourceFactory(const std::shared_ptr<VulkanDevice>& device);

            std::shared_ptr<ITextureResource> create_texture_resource(const std::string& resource_name) override;
            std::shared_ptr<IDepthResource> create_depth_resource(const std::string& resource_name) override;
    };
}

#endif
