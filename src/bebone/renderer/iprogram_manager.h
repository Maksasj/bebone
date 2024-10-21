#ifndef _BEBONE_RENDERER_IPROGRAM_MANAGER_H_
#define _BEBONE_RENDERER_IPROGRAM_MANAGER_H_

#include <string>
#include <unordered_map>

#include "renderer_backend.h"
#include "vertex.h"
#include "iprogram.h"
#include "ipass_impl.h"

namespace bebone::renderer {
    struct CachedProgramSource {
        std::string vert;
        std::string frag;
    };

    class IProgramManager : private NonCopyable {
        protected:
            std::unordered_map<std::string, CachedProgramSource> cached_sources;

        public:
            virtual ~IProgramManager() = default;

            virtual void cache_source(const char* name, const char* vertex_source, const char* fragment_source);
            virtual void cache_source(const std::string& name, const std::string& vertex_source, const std::string& fragment_source);

            [[nodiscard]] virtual CachedProgramSource get_source(const char* name) const;
            [[nodiscard]] virtual CachedProgramSource get_source(const std::string& name) const;

            virtual std::shared_ptr<IProgram> create_program(
                const std::shared_ptr<IPassImpl>& impl,
                const std::string& vertex_shader_code,
                const std::string& fragment_shader_code) = 0;
    };
}

#endif
