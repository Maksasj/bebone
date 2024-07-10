#ifndef _BEBONE_RENDERER_IPASS_H_
#define _BEBONE_RENDERER_IPASS_H_

#include <string>

#include "renderer_backend.h"
#include "icommand_encoder.h"

#include "iresource.h"
#include "resource_plug.h"
#include "ipass_assembler.h"

namespace bebone::renderer {
    class IPass {
        private:
            std::string name;

            std::vector<ResourcePlug> inputs;
            std::vector<ResourcePlug> outputs;

        protected:
            void register_input(const std::string& resource_name, std::shared_ptr<IResource>& resource);
            void register_output(const std::string& resource_name, std::shared_ptr<IResource>& resource);

        public:
            IPass(const std::string& name);
            virtual ~IPass() = default;

            virtual void assemble(IPassAssembler* assember) = 0;

            virtual void record(ICommandEncoder* encoder) = 0;
            virtual void reset() = 0;

            void plug_input(const std::string& resource_name, const std::shared_ptr<IResource>& resource);
            void plug_output(const std::string& resource_name, const std::shared_ptr<IResource>& resource);

            const std::string& get_name() const;
    };
}

#endif
