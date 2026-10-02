#include <fortrend/core/application_config.h>

#include <gtest/gtest.h>

#include <array>
#include <string_view>

TEST(
	ApplicationConfigValidationTest,
	AcceptsDefaultConfiguration)
{
	const fortrend::core::SApplicationConfig stConfig;

	const auto stResult =
		fortrend::core::validateApplicationConfig(stConfig);

	EXPECT_TRUE(stResult.has_value());
}

TEST(
	ApplicationConfigValidationTest,
	AcceptsSupportedEnvironments)
{
	constexpr std::array<std::string_view, 4>
		arrSupportedEnvironments{
			"local",
			"development",
			"test",
			"production"
		};

	for (const std::string_view sEnvironment :
		arrSupportedEnvironments)
	{
		fortrend::core::SApplicationConfig stConfig;
		stConfig.m_sEnvironment.assign(sEnvironment);

		const auto stResult =
			fortrend::core::validateApplicationConfig(
				stConfig);

		EXPECT_TRUE(stResult.has_value())
			<< "Environment: " << sEnvironment;
	}
}

TEST(
	ApplicationConfigValidationTest,
	RejectsEmptyServiceName)
{
	fortrend::core::SApplicationConfig stConfig;
	stConfig.m_sServiceName.clear();

	const auto stResult =
		fortrend::core::validateApplicationConfig(stConfig);

	ASSERT_FALSE(stResult.has_value());

	EXPECT_EQ(
		stResult.error().m_eCode,
		fortrend::core::EErrorCode::InvalidConfiguration);

	EXPECT_EQ(
		stResult.error().m_sMessage,
		"FORTREND_SERVICE_NAME must not be empty");
}

TEST(
	ApplicationConfigValidationTest,
	RejectsUnsupportedEnvironment)
{
	fortrend::core::SApplicationConfig stConfig;
	stConfig.m_sEnvironment = "invalid";

	const auto stResult =
		fortrend::core::validateApplicationConfig(stConfig);

	ASSERT_FALSE(stResult.has_value());

	EXPECT_EQ(
		stResult.error().m_eCode,
		fortrend::core::EErrorCode::InvalidConfiguration);

	EXPECT_EQ(
		stResult.error().m_sMessage,
		"FORTREND_ENV must be one of: "
		"local, development, test, production");
}