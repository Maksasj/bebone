#ifndef _BEBONE_CORE_ILOGGER_H_
#define _BEBONE_CORE_ILOGGER_H_

#include <iostream>
#include <ostream>
#include <cstdarg>
#include <format>

#include "log_level.h"

namespace bebone::core {
    class Logger;

    class ILogger {
        protected:
            virtual void log_impl(const LogLevel& log_level, std::string_view users_fmt, std::format_args&& args) = 0;

        public:
            virtual ~ILogger() = default;

            friend class Logger;
    };
}

#endif