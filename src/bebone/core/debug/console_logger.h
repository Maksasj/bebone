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
                LogLevel log_level;

            public:
                explicit ConsoleLogger(std::ostream& st = std::cout);

                void log(const LogLevel& level, std::string_view format, std::format_args&& args) override;

                void set_log_level(const LogLevel& level) override;
        };
}

#endif