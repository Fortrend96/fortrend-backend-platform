#include <fortrend/core/application_config.h>
#include <fortrend/core/error.h>
#include <fortrend/core/logger.h>

#include <iostream>

int main()
{
	const auto stConfigResult = fortrend::core::loadApplicationConfig();

	if (!stConfigResult)
	{
		const auto& stError = stConfigResult.error();

		std::cerr << "Startup error ["
				<< fortrend::core::errorCodeToString(stError.m_eCode)
				<< "]: "
				<< stError.m_sMessage
				<< "\n";

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