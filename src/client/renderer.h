#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "gpu_handles.h"
#include "transform.h"

using namespace bebone::core;
using namespace bebone::gfx;

class Renderer {
    public:
        virtual ~Renderer() {}

        virtual void record_draw_commands(VulkanCommandBuffer& cmd, PipelineLayout& pipelineLayout) = 0;
        virtual void calculate_transform(const Vec3f& position, const f32& scale, const Vec3f& rotation) = 0;
};

#endif
