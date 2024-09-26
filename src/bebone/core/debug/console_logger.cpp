#include "console_logger.h"

namespace bebone::core {
    ConsoleLogger::ConsoleLogger(std::ostream& st) : stream(st) {

    }

    std::ostream& ConsoleLogger::log(const LogLevel& logLevel) {
        switch (logLevel) {
            case LogLevel::Trace: return log_trace();
            case LogLevel::Debug: return log_debug();
            case LogLevel::Information: return log_information();
            case LogLevel::Warning: return log_warning();
            case LogLevel::Error: return log_error();
            case LogLevel::Critical: return log_critical();
        }
    }

    std::ostream& ConsoleLogger::log_trace() {
        return stream;
    }

    std::ostream& ConsoleLogger::log_debug() {
        return stream;
    }

    std::ostream& ConsoleLogger::log_information() {
        return stream;
    }

    std::ostream& ConsoleLogger::log_warning() {
        return stream;
    }

    std::ostream& ConsoleLogger::log_error() {
        return stream;
    }

    std::ostream& ConsoleLogger::log_critical() {
        return stream;
    }
}
