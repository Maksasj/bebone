#ifndef _BEBONE_GFX_BUFFER_IMPLEMENTATION_H_
#define _BEBONE_GFX_BUFFER_IMPLEMENTATION_H_

#include <vector>

#include "../common/common.h"

#include "gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::common;

    static std::vector<VkVertexInputBindingDescription> getBindingDescriptions() {
        std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
        
        bindingDescriptions[0].binding = 0;
        bindingDescriptions[0].stride = sizeof(Vertex);
        bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescriptions;
    }

    static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions() {
        std::vector<VkVertexInputAttributeDescription> atrributeDescriptions(2);
        
        atrributeDescriptions[0].binding = 0;
        atrributeDescriptions[0].location = 0;
        atrributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        atrributeDescriptions[0].offset = offsetof(Vertex, x);

        atrributeDescriptions[1].binding = 0;
        atrributeDescriptions[1].location = 1;
        atrributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        atrributeDescriptions[1].offset = offsetof(Vertex, r);

        return atrributeDescriptions;
    }

    class BufferImpl {
        private:

        public:
            virtual ~BufferImpl() {}
    };
}

#endif
