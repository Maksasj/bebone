#ifndef _BEBONE_RENDERER_IPRESENT_PASS_H_
#define _BEBONE_RENDERER_IPRESENT_PASS_H_

#include "igraphics_pass.h"
#include "mesh/quad_mesh_generator.h"

namespace bebone::renderer {
    class IPresentPass : public IGraphicsPass {
        protected:
            std::shared_ptr<IRenderTarget> render_target;
            std::shared_ptr<IAttachment> texture_attachment;

        protected:
            MeshHandle quad_mesh;

        public:
            IPresentPass(const std::shared_ptr<IPassImpl>& impl, const std::string& pass_name, const Vec2i& viewport);

            void assemble(std::shared_ptr<IPassAssembler>& assember) override;
            void record(ICommandEncoder* encoder) override;
    };
}

#endif
