#include "console_logger.h"

namespace bebone::core {
    ConsoleLogger::ConsoleLogger() : stream(std::cout) {

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
