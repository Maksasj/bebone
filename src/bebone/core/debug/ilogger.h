#ifndef _BEBONE_CORE_ILOGGER_H_
#define _BEBONE_CORE_ILOGGER_H_

#include <iostream>
#include <ostream>

#include "log_level.h"

namespace bebone::core {
    class ILogger {
        private:

        public:
            virtual ~ILogger() = default;

            virtual std::ostream& log(const LogLevel& logLevel) = 0;

            virtual std::ostream& log_trace() = 0;
            virtual std::ostream& log_debug() = 0;
            virtual std::ostream& log_information() = 0;
            virtual std::ostream& log_warning() = 0;
            virtual std::ostream& log_error() = 0;
            virtual std::ostream& log_critical() = 0;
    };
}

#endif