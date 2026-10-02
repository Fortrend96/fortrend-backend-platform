#include "fortrend/core/application_config.h"
#include "fortrend/core/error.h"

#include <cstdlib>
#include <expected>
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

std::expected<void, SError> validateApplicationConfig(
	const SApplicationConfig& stConfig
)
{
	if(stConfig.m_sServiceName.empty())
	{
		return std::unexpected(
			SError{
				EErrorCode::InvalidConfiguration,
				"FORTREND_SERVICE_NAME must not be empty"
			}
		);
	}

	if (!isSupportedEnvironment(stConfig.m_sEnvironment))
	{
		return std::unexpected(
			SError{
				EErrorCode::InvalidConfiguration,
				"FORTREND_ENV must be one of: "
				"local, development, test, production"
			}
		);
	}

	return {};
}


std::expected<SApplicationConfig, SError> loadApplicationConfig()
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

	const auto stValidationResult = validateApplicationConfig(stConfig);

	if (!stValidationResult)
	{
		return std::unexpected(stValidationResult.error());
	}

	return stConfig;
}


}