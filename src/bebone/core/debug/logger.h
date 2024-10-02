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
            template<typename... Args>
            static void log(const LogLevel& log_level, std::string_view users_fmt, Args&&... args) {
                get_instance()->log_impl(log_level, users_fmt, std::make_format_args(args...));
            }

            static std::unique_ptr<ILogger>& get_instance();
    };
}

#define LOG(LOG_LEVEL, FORMAT, ...) bebone::core::Logger::log(LOG_LEVEL, FORMAT, ##__VA_ARGS__)

#define LOG_TRACE(FORMAT, ...) bebone::core::Logger::log(LogLevel::Trace, FORMAT, ##__VA_ARGS__)
#define LOG_DEBUG(FORMAT, ...) bebone::core::Logger::log(LogLevel::Debug, FORMAT, ##__VA_ARGS__)
#define LOG_INFORMATION(FORMAT, ...) bebone::core::Logger::log(LogLevel::Information, FORMAT, ##__VA_ARGS__)
#define LOG_WARNING(FORMAT, ...) bebone::core::Logger::log(LogLevel::Warning, FORMAT, ##__VA_ARGS__)
#define LOG_ERROR(FORMAT, ...) bebone::core::Logger::log(LogLevel::Error, FORMAT, ##__VA_ARGS__)
#define LOG_CRITICAL(FORMAT, ...) bebone::core::Logger::log(LogLevel::Critical, FORMAT, ##__VA_ARGS__)

#endif