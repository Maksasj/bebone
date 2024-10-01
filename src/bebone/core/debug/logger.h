#ifndef _BEBONE_CORE_LOGGER_H_
#define _BEBONE_CORE_LOGGER_H_

#include <memory>

#include "ilogger.h"

#include "console_logger.h"

namespace bebone::core {
    // Global logger
    class Logger {
        private:
            std::unique_ptr<ILogger> logger_instance;

            Logger();

        public:
            static std::ostream& log(const LogLevel& logLevel);

            static std::ostream& log_trace();
            static std::ostream& log_debug();
            static std::ostream& log_information();
            static std::ostream& log_warning();
            static std::ostream& log_error();
            static std::ostream& log_critical();

            static std::unique_ptr<ILogger>& get_instance();
    };
}

#define LOG(LOG_LEVEL) bebone::core::Logger::log(LOG_LEVEL)

#define LOG_TRACE bebone::core::Logger::log_trace()
#define LOG_DEBUG bebone::core::Logger::log_debug()
#define LOG_INFORMATION bebone::core::Logger::log_debug()
#define LOG_WARNING bebone::core::Logger::log_debug()
#define LOG_ERROR bebone::core::Logger::log_debug()
#define LOG_CRITICAL bebone::core::Logger::log_debug()

#endif