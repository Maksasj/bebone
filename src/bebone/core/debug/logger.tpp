#ifndef _BEBONE_CORE_LOGGER_TPP_
#define _BEBONE_CORE_LOGGER_TPP_

#include <iostream>
#include <ostream>

#include "../memory/noncopyable.h"

#define BEBONE_LOGGER_DEFAULT_INSTANCE DEFAULT
#define BEBONE_LOGGER_ENABLE_LINE_BREAKS true
#define BEBONE_LOGGER_ENABLE_MESSAGE_TYPE true

namespace bebone::core {
    /// Logger instance specifying enum
    enum LOGGER_INSTANCE {
        DEFAULT
    };

    /// Logger message type enum
    enum LOG_MESSAGE_TYPE {
        INFO,
        WARNING,
        ERROR,
        CRITICAL_ERROR
    };

    /// Class that can be used for logging,
    template<LOGGER_INSTANCE __loggerInstance = DEFAULT>
    class Logger : private NonCopyable {
        private:
            std::ostream& stream;

            Logger() : stream(std::cout) {}

            /*!
             * Function that returns singleton instance of logger
             * @return Logger instance
            */
            static Logger& get_instance() {
                static Logger logger;

                return logger;
            }

            /*!
             * Function that converts LOG_MESSAGE_TYPE enum value into the string
             * @param messageType - message type
             * @return Message type string
            */
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
            /*!
             * Function used for setting specific output stream
             * @param stream - desired stream
            */
            static void set_stream(const std::ostream& stream) {
                Logger<__loggerInstance>::get_instance().stream = stream;
            }

            /*!
             * Function used for logging a message
             * @tparam messageType - message type
             * @param logMessage - message
            */
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

            /*!
             * Function used for logging a message
             * @tparam messageType - message type
             * @param logMessage - message
            */
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