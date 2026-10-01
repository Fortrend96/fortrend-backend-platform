#include <fortrend/core/application_config.h>

#include <cstdlib>
#include <string_view>

namespace
{

bool isSupportedEnvironment(std::string_view sEnvironment)
{
	return
		sEnvironment == "local" ||
		sEnvironment == "development" ||
		sEnvironment == "test" ||
		sEnvironment == "production";
}

}

namespace fortrend::core
{

std::expected<SApplicationConfig, std::string> loadApplicationConfig()
{
	SApplicationConfig stConfig;

	if (const char* pszServiceName = std::getenv("FORTREND_SERVICE_NAME");
		pszServiceName != nullptr)
	{
		stConfig.m_sServiceName = pszServiceName;
	}

	if (const char* pszEnvironment = std::getenv("FORTREND_ENV");
		pszEnvironment != nullptr)
	{
		stConfig.m_sEnvironment = pszEnvironment;
	}

	if (stConfig.m_sServiceName.empty())
	{
		return std::unexpected(
			"FORTREND_SERVICE_NAME must not be empty");
	}

	if (!isSupportedEnvironment(stConfig.m_sEnvironment))
	{
		return std::unexpected(
			"FORTREND_ENV must be one of: "
			"local, development, test, production");
	}

	return stConfig;
}

}