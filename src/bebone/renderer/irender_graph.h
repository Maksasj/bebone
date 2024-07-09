#ifndef _BEBONE_RENDERER_IRENDER_GRAPH_H_
#define _BEBONE_RENDERER_IRENDER_GRAPH_H_

#include "renderer_backend.h"

#include "ipass.h"
#include "ipass_factory.h"

namespace bebone::renderer {
    class IRenderGraph {
        private:
            std::vector<std::shared_ptr<IPass>> render_passes;

        public:
            IRenderGraph();

            virtual void execute() = 0;
            virtual void reset() = 0;


            virtual std::shared_ptr<IPassFactory> create_pass_factory() const;

            void append_pass(std::shared_ptr<IPass>& render_pass);
            std::optional<std::shared_ptr<IPass>> get_render_pass(const std::string& pass_name) const;
    };
}

#endif
