#include <fortrend/core/error.h>

#include <gtest/gtest.h>

TEST(ErrorTest, ConvertsErrorCodesToStableStrings)
{
	EXPECT_EQ(
        fortrend::core::errorCodeToString(
            fortrend::core::EErrorCode::InvalidConfiguration), 
            "invalid_configuration");

	EXPECT_EQ(
		fortrend::core::errorCodeToString(
			fortrend::core::EErrorCode::InternalError),
		"internal_error");
}

TEST(
	ErrorTest,
	MapsErrorCodesToExitCodes)
{
	EXPECT_EQ(
		fortrend::core::errorCodeToExitCode(
			fortrend::core::EErrorCode::InvalidConfiguration),
		2);

	EXPECT_EQ(
		fortrend::core::errorCodeToExitCode(
			fortrend::core::EErrorCode::InternalError),
		1);
}