#include "bebone/core/debug/log_level.h"
#include "gtest/gtest.h"

using namespace bebone::core;

TEST(LogLevelTestSuite, UnixLogLevelColorReturnsCorrectColor) {
    std::string result = unix_log_level_color(LogLevel::Trace);
    ASSERT_EQ(result, UnixConsoleColors::White);

    result = unix_log_level_color(LogLevel::Debug);
    ASSERT_EQ(result, UnixConsoleColors::Cyan);

    result = unix_log_level_color(LogLevel::Information);
    ASSERT_EQ(result, UnixConsoleColors::Green);

    result = unix_log_level_color(LogLevel::Warning);
    ASSERT_EQ(result, UnixConsoleColors::Yellow);

    result = unix_log_level_color(LogLevel::Error);
    ASSERT_EQ(result, UnixConsoleColors::Red);

    result = unix_log_level_color(LogLevel::Critical);
    ASSERT_EQ(result, UnixConsoleColors::DarkRed);
}

TEST(LogLevelTestSuite, StringifyLogLevelReturnsCorrectString) {
    std::string result = stringify_log_level(LogLevel::Trace);
    ASSERT_EQ(result, "TRC");

    result = stringify_log_level(LogLevel::Debug);
    ASSERT_EQ(result, "DGB");

    result = stringify_log_level(LogLevel::Information);
    ASSERT_EQ(result, "INF");

    result = stringify_log_level(LogLevel::Warning);
    ASSERT_EQ(result, "WAR");

    result = stringify_log_level(LogLevel::Error);
    ASSERT_EQ(result, "ERR");

    result = stringify_log_level(LogLevel::Critical);
    ASSERT_EQ(result, "CRI");
}
