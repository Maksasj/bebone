#ifndef _BEBONE_RENDERER_IRENDER_GRAPH_H_
#define _BEBONE_RENDERER_IRENDER_GRAPH_H_

#include "renderer_backend.h"

#include "ipass.h"
#include "ipass_factory.h"
#include "iresource_factory.h"

namespace bebone::renderer {
    class IRenderGraph {
        private:
            std::vector<std::shared_ptr<IPass>> render_passes;
            std::vector<std::shared_ptr<IResource>> render_resources;

        public:
            IRenderGraph();
            virtual ~IRenderGraph() = default;

            virtual void record() = 0;
            virtual void build() = 0;

            virtual void submit() = 0;
            virtual void reset() = 0;

            void add_pass(const std::shared_ptr<IPass>& render_pass);
            std::optional<std::shared_ptr<IPass>> get_render_pass(const std::string& pass_name) const;
            std::vector<std::shared_ptr<IPass>>& get_render_passes();

            void add_resource(const std::shared_ptr<IResource>& render_resource);
            std::optional<std::shared_ptr<IResource>> get_render_resource(const std::string& resource_name) const;
            std::vector<std::shared_ptr<IResource>>& get_render_resources();

            virtual std::shared_ptr<IPassFactory> create_pass_factory() const = 0;
            virtual std::shared_ptr<IResourceFactory> create_resource_factory() const = 0;
    };
}

#endif
