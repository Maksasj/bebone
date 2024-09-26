#include "logger.h"

namespace bebone::core {
    Logger::Logger() {
        logger_instance = std::make_unique<ConsoleLogger>();
    }

    std::ostream& Logger::log_trace() {
        return get_instance()->log_trace();
    }

    std::ostream& Logger::log_debug() {
        return get_instance()->log_debug();
    }

    std::ostream& Logger::log_information() {
        return get_instance()->log_information();
    }

    std::ostream& Logger::log_warning() {
        return get_instance()->log_warning();
    }

    std::ostream& Logger::log_error() {
        return get_instance()->log_error();
    }

    std::ostream& Logger::log_critical() {
        return get_instance()->log_critical();
    }

    std::unique_ptr<ILogger>& Logger::get_instance() {
        static Logger logger;
        return logger.logger_instance;
    }
}
