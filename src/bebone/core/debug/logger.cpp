#include "logger.h"

namespace bebone::core {
    Logger::Logger() {
        logger_instance = std::make_unique<ConsoleLogger>();
    }

    std::unique_ptr<ILogger>& Logger::get_instance() {
        static Logger logger;
        return logger.logger_instance;
    }
}
