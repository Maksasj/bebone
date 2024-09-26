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
}

#endif