#ifndef _BEBONE_CORE_LOGGER_TPP_
#define _BEBONE_CORE_LOGGER_TPP_

#include <iostream>
#include <ostream>

#include "../memory/noncopyable.h"

#define BEBONE_LOGGER_DEFAULT_INSTANCE Default
#define BEBONE_LOGGER_ENABLE_LINE_BREAKS true
#define BEBONE_LOGGER_ENABLE_MESSAGE_TYPE true

namespace bebone::core {
    /// Logger instance specifying enum
    enum LoggerInstance {
        Default
    };

    /// Logger message type enum
    enum LogMessageType {
        Info,
        Warning,
        Error,
        CriticalError
    };

    /// Class that can be used for logging,
    template<LoggerInstance logger_instance = Default>
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
             * Function that converts LogMessageType enum value into the string
             * @param message_type - message type
             * @return Message type string
            */
            constexpr static const char* get_message_type_string(const LogMessageType& message_type) {
                switch (message_type) {
                    case Info: return "INFO";
                    case Warning: return "WARNING";
                    case Error: return "ERROR";
                    case CriticalError: return "CRITICAL ERROR";
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
                Logger<logger_instance>::get_instance().stream = stream;
            }

            /*!
             * Function used for logging a message
             * @tparam message_type - message type
             * @param log_message - message
            */
            template<LogMessageType message_type>
            static void log(const std::string& log_message) {
                auto& stream = Logger<logger_instance>::get_instance().stream;

                if constexpr (BEBONE_LOGGER_ENABLE_MESSAGE_TYPE) {
                    stream << "[" << get_message_type_string(message_type) << "]";
                }

                stream << log_message;

                if constexpr (BEBONE_LOGGER_ENABLE_LINE_BREAKS) {
                    stream << "\n";
                }
            }

            /*!
             * Function used for logging a message
             * @tparam message_type - message type
             * @param log_message - message
            */
            template<LogMessageType message_type>
            static void log(const char* log_message) {
                auto& stream = Logger<logger_instance>::get_instance().stream;

                if constexpr (BEBONE_LOGGER_ENABLE_MESSAGE_TYPE) {
                    stream << "[" << get_message_type_string(message_type) << "]";
                }

                stream << log_message;

                if constexpr (BEBONE_LOGGER_ENABLE_LINE_BREAKS) {
                    stream << "\n";
                }
            }
    };
}

#endif