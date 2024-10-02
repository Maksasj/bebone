#ifndef _BEBONE_CORE_ILOGGER_H_
#define _BEBONE_CORE_ILOGGER_H_

#include <iostream>
#include <ostream>
#include <cstdarg>
#include <format>

#include "log_level.h"

namespace bebone::core {
    class ILogger {
        protected:

        public:
            virtual ~ILogger() = default;

            virtual void log(const LogLevel& level, std::string_view format, std::format_args&& args) = 0;

            virtual void set_log_level(const LogLevel& level) = 0;
    };
}

#endif