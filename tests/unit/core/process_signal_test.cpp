#include <fortrend/core/process_signal.h>

#include <gtest/gtest.h>

#include <signal.h>

#include <string_view>

TEST(ProcessSignalTest, ConvertsSupportedSignalsToStableNames)
{
	EXPECT_EQ(
		fortrend::core::signalToString(SIGINT),
		std::string_view{ "SIGINT" }
    );

	EXPECT_EQ(
		fortrend::core::signalToString(SIGTERM),
		std::string_view{ "SIGTERM" }
    );

	EXPECT_EQ(
		fortrend::core::signalToString(0),
		std::string_view{ "UNKNOWN" }
    );
}