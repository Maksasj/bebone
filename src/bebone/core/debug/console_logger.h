#ifndef _BEBONE_CORE_CONSOLE_LOGGER_H_
#define _BEBONE_CORE_CONSOLE_LOGGER_H_

#include "ilogger.h"

namespace bebone::core {
        class ConsoleLogger : public ILogger  {
            private:
                std::ostream& stream;

            public:
                ConsoleLogger();

                std::ostream& log_trace() override;
                std::ostream& log_debug() override;
                std::ostream& log_information() override;
                std::ostream& log_warning() override;
                std::ostream& log_error() override;
                std::ostream& log_critical() override;
        };
}

#endif