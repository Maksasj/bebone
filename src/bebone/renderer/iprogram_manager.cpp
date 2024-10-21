#include "iprogram_manager.h"

namespace bebone::renderer {
    void IProgramManager::cache_source(const char* name, const char* vertex_source, const char* fragment_source) {
        cached_sources[name] = { vertex_source, fragment_source };
    }

    void IProgramManager::cache_source(const std::string& name, const std::string& vertex_source, const std::string& fragment_source) {
        cached_sources[name] = { vertex_source, fragment_source };
    }

    CachedProgramSource IProgramManager::get_source(const char* name) const {
        return cached_sources.at(name);
    }

    CachedProgramSource IProgramManager::get_source(const std::string& name) const {
        return cached_sources.at(name);
    }
}
