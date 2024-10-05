#include "bebone/core/debug/console_logger.h"
#include "gtest/gtest.h"

using namespace bebone::core;

TEST(LogLevelTestSuite, ConsoleLoggerLogsMessages) {
    std::stringstream ss;
    auto logger = ConsoleLogger(ss);

    ASSERT_EQ(ss.str().size(), 0);

    logger.log(LogLevel::Trace, "Test log message");
    ASSERT_EQ(ss.str().size(), 52);

    logger.log(LogLevel::Trace, "Another message");
    ASSERT_EQ(ss.str().size(), 103);
}
