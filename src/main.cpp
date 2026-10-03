#include <fortrend/core/application_config.h>
#include <fortrend/core/error.h>
#include <fortrend/core/logger.h>
#include <fortrend/core/process_signal.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include <unistd.h>

int main()
{
	const auto stConfigResult = fortrend::core::loadApplicationConfig();

	if (!stConfigResult)
	{
		const auto& stError = stConfigResult.error();

		std::cerr
			<< "Startup error ["
			<< fortrend::core::errorCodeToString(
				stError.m_eCode)
			<< "]: "
			<< stError.m_sMessage
			<< '\n';

		return fortrend::core::errorCodeToExitCode(stError.m_eCode);
	}

	const auto& stConfig = *stConfigResult;

	const fortrend::core::CLogger logger(
		stConfig.m_sServiceName,
		stConfig.m_sEnvironment
	);

	const auto stSignalResult = fortrend::core::installShutdownSignalHandlers();

	if (!stSignalResult)
	{
		const auto& stError = stSignalResult.error();

		std::string sMessage{"startup error ["};

		sMessage +=
			fortrend::core::errorCodeToString(stError.m_eCode);

		sMessage += "]: ";
		sMessage += stError.m_sMessage;

		logger.error(sMessage);

		return fortrend::core::errorCodeToExitCode(stError.m_eCode);
	}

	std::string sStartupMessage{"application started; pid="};

	sStartupMessage += std::to_string(static_cast<long long>(::getpid()));

	logger.info(sStartupMessage);

	while (!fortrend::core::isShutdownRequested())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
	}

	std::string sShutdownMessage{"shutdown requested by "};

	sShutdownMessage.append(
		fortrend::core::signalToString(
			fortrend::core::shutdownSignal()));

	logger.info(sShutdownMessage);
	logger.info("application stopped");

	return 0;
}