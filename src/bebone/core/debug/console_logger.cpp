#include "console_logger.h"

namespace bebone::core {
    ConsoleLogger::ConsoleLogger(std::ostream& st)
        : stream(st), log_level(LogLevel::Trace) {

    }

    void ConsoleLogger::log(const LogLevel& level, std::string_view format) {
        if(level < log_level)
            return;

        auto log_level_str = stringify_log_level(level);
        auto log_level_color = unix_log_level_color(level);

        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        // Todo add this
        // const std::source_location& location = std::source_location::current();

        std::ostringstream time_stream;
        time_stream << std::put_time(&tm, "%H:%M:%S");
        auto formatted_time = time_stream.str();

        const auto prefix = std::format("{}[{} {}{}{}] ", UnixConsoleColors::Gray, formatted_time, log_level_color, log_level_str, UnixConsoleColors::Gray);

        stream << prefix << UnixConsoleColors::Default << format << std::endl;
    }

    void ConsoleLogger::log(const LogLevel& level, std::string_view format, std::format_args&& args) {
        if(level < log_level)
            return;

        auto log_level_str = stringify_log_level(level);
        auto log_level_color = unix_log_level_color(level);

        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        // Todo add this
        // const std::source_location& location = std::source_location::current();

        std::ostringstream time_stream;
        time_stream << std::put_time(&tm, "%H:%M:%S");
        auto formatted_time = time_stream.str();

        const auto prefix = std::format("{}[{} {}{}{}] ", UnixConsoleColors::Gray, formatted_time, log_level_color, log_level_str, UnixConsoleColors::Gray);

        stream << prefix << UnixConsoleColors::Default << std::vformat(format, args) << std::endl;
    }

    void ConsoleLogger::set_log_level(const LogLevel& level) {
        log_level = level;
    }
}
