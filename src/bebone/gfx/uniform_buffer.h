#ifndef _BEBONE_GFX_UNIFORM_BUFFER_H_
#define _BEBONE_GFX_UNIFORM_BUFFER_H_

#include <memory>

#include "vulkan_uniform_buffer_impl.h"

namespace bebone::gfx {
    class UniformBuffer {
        private:
            std::vector<VulkanUniformBufferImpl*> _impl; 

            UniformBuffer(std::vector<VulkanUniformBufferImpl*> impl) : _impl(impl) {

            }

        public:
            ~UniformBuffer() {
                for(const auto& buf : _impl) {
                    delete buf;
                }

                _impl.clear();
            }

            VulkanBufferImpl* get_impl(const size_t index) {
                return _impl[index];
            }

            size_t get_impl_size() const {
                return _impl.size();
            }

            template<class Impl, class... Args>
            static UniformBuffer create_from_impl(const size_t fif, Args&&... args) {
                std::vector<VulkanUniformBufferImpl*> impl;

                for(size_t f = 0; f < fif; ++f) {
                    impl.push_back(new Impl(std::forward<Args>(args)...));
                }
                
                return UniformBuffer(impl);
            }
    };
}

#endif
