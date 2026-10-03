#include <fortrend/core/process_signal.h>

#include <cerrno>
#include <signal.h>

#include <string>
#include <string_view>
#include <system_error>

namespace
{

volatile sig_atomic_t g_nShutdownSignal = 0;

void shutdownSignalHandler(int nSignal)
{
	g_nShutdownSignal =
		static_cast<sig_atomic_t>(nSignal);
}

fortrend::core::SError makeSignalHandlerSetupError(
	std::string_view sOperation,
	int nError)
{
	std::string sMessage{ sOperation };

	sMessage += " failed: ";
	sMessage += std::error_code(
		nError,
		std::generic_category()).message();

	return fortrend::core::SError{
		fortrend::core::EErrorCode::SignalHandlerSetupFailed,
		std::move(sMessage)
	};
}

}

namespace fortrend::core
{

std::expected<void, SError> installShutdownSignalHandlers()
{
	g_nShutdownSignal = 0;

	struct sigaction stAction
	{
	};

	stAction.sa_handler = shutdownSignalHandler;
	stAction.sa_flags = 0;

	if (::sigemptyset(&stAction.sa_mask) == -1)
	{
		const int nError = errno;

		return std::unexpected(
			makeSignalHandlerSetupError(
				"sigemptyset",
				nError));
	}

	struct sigaction stPreviousSigInt
	{
	};

	if (::sigaction(
			SIGINT,
			&stAction,
			&stPreviousSigInt) == -1)
	{
		const int nError = errno;

		return std::unexpected(
			makeSignalHandlerSetupError(
				"sigaction(SIGINT)",
				nError));
	}

	if (::sigaction(
			SIGTERM,
			&stAction,
			nullptr) == -1)
	{
		const int nError = errno;

		(void)::sigaction(
			SIGINT,
			&stPreviousSigInt,
			nullptr);

		return std::unexpected(
			makeSignalHandlerSetupError(
				"sigaction(SIGTERM)",
				nError));
	}

	return {};
}

bool isShutdownRequested() noexcept
{
	return g_nShutdownSignal != 0;
}

int shutdownSignal() noexcept
{
	return static_cast<int>(
		g_nShutdownSignal);
}

std::string_view signalToString(int nSignal) noexcept
{
	switch (nSignal)
	{
		case SIGINT:
			return "SIGINT";

		case SIGTERM:
			return "SIGTERM";
	}

	return "UNKNOWN";
}

}