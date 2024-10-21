#ifndef _BEBONE_CORE_LOG_LEVEL_H_
#define _BEBONE_CORE_LOG_LEVEL_H_

namespace bebone::core {
    enum class LogLevel {
        Trace,
        Debug,
        Information,
        Warning,
        Error,
        Critical
        // None
    };

    struct UnixConsoleColors {
        constexpr static const char* Default = "\x1B[39m";
        constexpr static const char* Black = "\x1B[30m";
        constexpr static const char* DarkRed = "\x1B[31m";
        constexpr static const char* DarkGreen = "\x1B[32m";
        constexpr static const char* DarkYellow = "\x1B[33m";
        constexpr static const char* DarkBlue = "\x1B[34m";
        constexpr static const char* DarkMagenta = "\x1B[35m";
        constexpr static const char* DarkCyan = "\x1B[36m";
        constexpr static const char* Gray = "\x1B[37m";
        constexpr static const char* DarkGray = "\x1B[90m";
        constexpr static const char* Red = "\x1B[91m";
        constexpr static const char* Green = "\x1B[92m";
        constexpr static const char* Yellow = "\x1B[93m";
        constexpr static const char* Blue = "\x1B[94m";
        constexpr static const char* Magenta = "\x1B[95m";
        constexpr static const char* Cyan = "\x1B[96m";
        constexpr static const char* White = "\x1B[97m";
    };

    static inline const char* unix_log_level_color(const LogLevel& log_level) {
        switch (log_level) {
            case LogLevel::Trace:           { return UnixConsoleColors::White; }
            case LogLevel::Debug:           { return UnixConsoleColors::Cyan; }
            case LogLevel::Information:     { return UnixConsoleColors::Green; }
            case LogLevel::Warning:         { return UnixConsoleColors::Yellow; }
            case LogLevel::Error:           { return UnixConsoleColors::Red; }
            case LogLevel::Critical:        { return UnixConsoleColors::DarkRed; }
        }
    }

    static inline const char* stringify_log_level(const LogLevel& log_level) {
        switch (log_level) {
            case LogLevel::Trace:           { return "TRC"; }
            case LogLevel::Debug:           { return "DGB"; }
            case LogLevel::Information:     { return "INF"; }
            case LogLevel::Warning:         { return "WAR"; }
            case LogLevel::Error:           { return "ERR"; }
            case LogLevel::Critical:        { return "CRI"; }
        }
    }
}

#endif