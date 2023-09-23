#ifndef _RENDERING_WORLD_H_
#define _RENDERING_WORLD_H_

#include <vector>
#include "object.h"

#include "box_renderer.h"

class RenderingWorld {
    private:
        VulkanRenderer& renderer;
        std::vector<Object*> objects;

    public:
        RenderingWorld(VulkanRenderer& _renderer) : renderer(_renderer) {
        
        }

        ~RenderingWorld() {

        }

        void add_object(Object* object, GPUResourceManager& resourceManager, GPUResourceSet& resourceSet) {
            object->renderer = new BoxRenderer(renderer, resourceManager, resourceSet);
            objects.push_back(object);
        }

        void record_draw_commands(VulkanCommandBuffer& cmd, PipelineLayout& pipelineLayout) {
            for(Object* object : objects) {
                object->renderer->calculate_transform(object->position, object->scale, object->rotation);
                object->renderer->record_draw_commands(cmd, pipelineLayout);
            }
        }
};

#endif
