#include <fortrend/core/application_config.h>
#include <fortrend/core/logger.h>

#include <iostream>

int main()
{
	const auto stConfigResult = fortrend::core::loadApplicationConfig();

	if (!stConfigResult)
	{
		std::cerr << "Configuration error: " << stConfigResult.error() << '\n';

		return 1;
	}

	const auto& stConfig = *stConfigResult;

	const fortrend::core::CLogger logger(
		stConfig.m_sServiceName,
		stConfig.m_sEnvironment
	);

	logger.info("application started");

	return 0;
}