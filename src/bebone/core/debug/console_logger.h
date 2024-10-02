#ifndef _BEBONE_CORE_CONSOLE_LOGGER_H_
#define _BEBONE_CORE_CONSOLE_LOGGER_H_

#include <format>
#include <ctime>
#include <iomanip>
#include <source_location>
#include <sstream>

#include "ilogger.h"

namespace bebone::core {
        class ConsoleLogger : public ILogger  {
            private:
                std::ostream& stream;

            public:
                explicit ConsoleLogger(std::ostream& st = std::cout);

                void log(const LogLevel& log_level, std::string_view users_fmt, std::format_args&& args) override;
        };
}

#endif