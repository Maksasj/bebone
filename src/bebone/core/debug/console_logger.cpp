#include "console_logger.h"

namespace bebone::core {
    ConsoleLogger::ConsoleLogger(std::ostream& st) : stream(st) {

    }

    void ConsoleLogger::log(const LogLevel& log_level, std::string_view users_fmt, std::format_args&& args) {
        const auto& log_level_str = stringify_log_level(log_level);
        const auto& log_level_color = unix_log_level_color(log_level);

        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        // Todo add this
        // const std::source_location& location = std::source_location::current();

        std::ostringstream time_stream;
        time_stream << std::put_time(&tm, "%H:%M:%S");
        auto formatted_time = time_stream.str();

        const auto prefix = std::format("{}[{} {}{}{}] ", UnixConsoleColors::Gray, formatted_time, log_level_color, log_level_str, UnixConsoleColors::Gray);

        stream << prefix << UnixConsoleColors::Default << std::vformat(users_fmt, args) << std::endl;
    }
}
