#ifndef _BEBONE_GFX_RENDERER_H_
#define _BEBONE_GFX_RENDERER_H_

#include <memory>

#include "renderer_impl.h"

namespace bebone::gfx {
    class Renderer {
        private:
            RendererImpl* _impl;

            Renderer(RendererImpl* impl) : _impl(impl) {

            }

        public:
            ~Renderer() {
                if(_impl != nullptr) {
                    delete _impl;
                }
            }

            CommandBuffer& get_command_buffer() {
                return _impl->get_command_buffer();
            }

            CommandBufferPool& get_command_buffer_pool() {
                return _impl->get_command_buffer_pool();
            }

            DescriptorPool& get_descriptor_pool() {
                return _impl->get_descriptor_pool();
            }

            Pipeline create_pipeline(PipelineLayout& pipelineLayout, const std::vector<unsigned int>& vertexSpirvCode, const std::vector<unsigned int>& fragmentSpirvCode) {
                return _impl->create_pipeline(pipelineLayout, vertexSpirvCode, fragmentSpirvCode);
            }

            VertexBuffer create_vertex_buffer(const std::vector<Vertex>& vertices) {
                return _impl->create_vertex_buffer(vertices);
            }

            IndexBuffer create_index_buffer(const std::vector<int>& indices) {
                return _impl->create_index_buffer(indices);
            }

            PipelineLayout create_pipeline_layout() {
                return _impl->create_pipeline_layout();
            }

            std::shared_ptr<MyEngineSwapChainImpl> get_swap_chain() {
                return _impl->get_swap_chain();
            }

            void present() {
                _impl->present();
            }

            RendererImpl* get_impl() {
                return _impl;
            }

            template<class Impl, class... Args>
            static Renderer create_from_impl(Args&&... args) {
                return Renderer(new Impl(std::forward<Args>(args)...));
            }

            template<class... Args>
            static Renderer create(const RenderingApi& api, Args&&... args) {
                switch (api) {
                    case VULKAN: return Renderer(new VulkanRendererImpl(std::forward<Args>(args)...));
                    default: throw std::runtime_error("Renderer is not implemented for this rendering api");
                }

                throw std::runtime_error("Failed to create renderer");
            }
    };
}

#endif
