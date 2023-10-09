#ifndef _BEBONE_CORE_LOGGER_TPP_
#define _BEBONE_CORE_LOGGER_TPP_

#include <iostream>
#include <ostream>

#include "noncopyable.h"

#define BEBONE_LOGGER_DEFAULT_INSTANCE DEFAULT
#define BEBONE_LOGGER_ENABLE_LINE_BREAKS true
#define BEBONE_LOGGER_ENABLE_MESSAGE_TYPE true

namespace bebone::core {
    enum LOGGER_INSTANCE {
        DEFAULT
    };

    enum LOG_MESSAGE_TYPE {
        INFO,
        WARNING,
        ERROR,
        CRITICAL_ERROR
    };

    template<LOGGER_INSTANCE __loggerInstance = DEFAULT>
    class Logger : private NonCopyable {
        private:
            std::ostream& stream;

            Logger() : stream(std::cout) {}

            static Logger& get_instance() {
                static Logger logger;

                return logger;
            }

            constexpr static const char* get_message_type_string(const LOG_MESSAGE_TYPE& messageType) {
                switch (messageType) {
                    case INFO: return "INFO";
                    case WARNING: return "WARNING";
                    case ERROR: return "ERROR";
                    case CRITICAL_ERROR: return "CRITICAL ERROR";
                    default: return "UNNAMED";
                }
                
                return "UNNAMED";
            }

        public:
            static void set_stream(const std::ostream& stream) {
                Logger<__loggerInstance>::get_instance().stream = stream;
            }

            template<LOG_MESSAGE_TYPE messageType>
            static void log(const std::string& logMessage) {
                auto& stream = Logger<__loggerInstance>::get_instance().stream;

                if constexpr (BEBONE_LOGGER_ENABLE_MESSAGE_TYPE) {
                    stream << "[" << get_message_type_string(messageType) << "]";
                }

                stream << logMessage;

                if constexpr (BEBONE_LOGGER_ENABLE_LINE_BREAKS) {
                    stream << "\n";
                }
            }

            template<LOG_MESSAGE_TYPE messageType>
            static void log(const char* logMessage) {
                auto& stream = Logger<__loggerInstance>::get_instance().stream;

                if constexpr (BEBONE_LOGGER_ENABLE_MESSAGE_TYPE) {
                    stream << "[" << get_message_type_string(messageType) << "]";
                }

                stream << logMessage;

                if constexpr (BEBONE_LOGGER_ENABLE_LINE_BREAKS) {
                    stream << "\n";
                }
            }
    };
}

#endif