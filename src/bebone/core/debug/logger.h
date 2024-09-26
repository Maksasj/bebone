#ifndef _BEBONE_CORE_LOGGER_H_
#define _BEBONE_CORE_LOGGER_H_

#include "ilogger.h"

#include "console_logger.h"

namespace bebone::core {
    // Global logger
    class Logger {
        private:
            std::unique_ptr<ILogger> logger_instance;

            Logger();

        public:
            static std::ostream& log_trace();
            static std::ostream& log_debug();
            static std::ostream& log_information();
            static std::ostream& log_warning();
            static std::ostream& log_error();
            static std::ostream& log_critical();

            static std::unique_ptr<ILogger>& get_instance();
    };
}

#endif