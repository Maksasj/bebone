#ifndef _BEBONE_RENDERER_IPASS_H_
#define _BEBONE_RENDERER_IPASS_H_

#include <string>

#include "renderer_backend.h"

namespace bebone::renderer {
    class IPass {
        private:
            std::string name;

        public:
            IPass(const std::string& name);
            virtual ~IPass() = default;

            virtual void execute() = 0;
            virtual void reset() = 0;

            const std::string& get_name() const;
    };

    class IGeometryPass : public IPass {
        private:

        public:
            IGeometryPass(const std::string& pass_name) : IPass(pass_name) {

            }
    };

    class IPresentPass : public IPass {
        private:

        public:
            IPresentPass(const std::string& pass_name) : IPass(pass_name) {

            }
    };
}

#endif
