#include <fortrend/core/application_config.h>

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

	std::cout << "Fortrend Backend Platform" << '\n';
	std::cout << "Service: " << stConfig.m_sServiceName << '\n';
	std::cout << "Environment: " << stConfig.m_sEnvironment << '\n';

	return 0;
}