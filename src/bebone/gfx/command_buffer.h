#ifndef _BEBONE_GFX_COMMAND_BUFFER_H_
#define _BEBONE_GFX_COMMAND_BUFFER_H_

#include "../core/arena_allocator.h"

#include "gfx_backend.h"

#include "commands.h"

namespace bebone::gfx {
    class CommandBuffer {
        private:

        protected:
            virtual void* push_iternal(const size_t&) = 0;

        public:
            virtual void begin_record() = 0;
            virtual void end_record() = 0;

            template<class CommandType, class... Args>
            void* push(Args&&... args) {
                CommandType* ptr = static_cast<CommandType*>(this->push_iternal(sizeof(CommandType)));
                
                if(ptr == nullptr) {
                    throw std::runtime_error("Failed to allocate memory for command");
                }

                *ptr = CommandType(std::forward<Args>(args)...);
            }

            virtual void preprocess() = 0;
    };
}

#endif
