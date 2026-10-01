#include <fortrend/core/logger.h>

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <sstream>
#include <syncstream>
#include <utility>

namespace
{

std::string_view logLevelToString(fortrend::core::ELogLevel eLevel)
{
	switch (eLevel)
	{
		case fortrend::core::ELogLevel::Info:
			return "INFO";

		case fortrend::core::ELogLevel::Warning:
			return "WARNING";

		case fortrend::core::ELogLevel::Error:
			return "ERROR";
	}

	return "UNKNOWN";
}

std::string makeUtcTimestamp()
{
	using namespace std::chrono;

	const auto tpNow = system_clock::now();

	const auto dMilliseconds =
		duration_cast<milliseconds>(tpNow.time_since_epoch()) %
		seconds(1);

	const std::time_t nTime =
		system_clock::to_time_t(tpNow);

	std::tm stUtcTime{};

	if (gmtime_r(&nTime, &stUtcTime) == nullptr)
	{
		return "1970-01-01T00:00:00.000Z";
	}

	std::ostringstream stream;

	stream
		<< std::put_time(
			&stUtcTime,
			"%Y-%m-%dT%H:%M:%S")
		<< '.'
		<< std::setw(3)
		<< std::setfill('0')
		<< dMilliseconds.count()
		<< 'Z';

	return stream.str();
}

std::string escapeJson(std::string_view sValue)
{
	constexpr char arrHexDigits[] =
		"0123456789abcdef";

	std::string sEscaped;
	sEscaped.reserve(sValue.size());

	for (const char ch : sValue)
	{
		switch (ch)
		{
			case '"':
				sEscaped += "\\\"";
				break;

			case '\\':
				sEscaped += "\\\\";
				break;

			case '\b':
				sEscaped += "\\b";
				break;

			case '\f':
				sEscaped += "\\f";
				break;

			case '\n':
				sEscaped += "\\n";
				break;

			case '\r':
				sEscaped += "\\r";
				break;

			case '\t':
				sEscaped += "\\t";
				break;

			default:
			{
				const auto uch 
                    = static_cast<unsigned char>(ch);

				if (uch < 0x20)
				{
					sEscaped += "\\u00";

					sEscaped += arrHexDigits[static_cast<std::size_t>(uch >> 4)];

					sEscaped += arrHexDigits[static_cast<std::size_t>(uch & 0x0F)];
				}
				else
				{
					sEscaped += ch;
				}

				break;
			}
		}
	}

	return sEscaped;
}

}

namespace fortrend::core
{

CLogger::CLogger(
	std::string sServiceName,
	std::string sEnvironment)
	: m_sServiceName(std::move(sServiceName))
	  , m_sEnvironment(std::move(sEnvironment))
{
}

void CLogger::log(
	ELogLevel eLevel,
	std::string_view sMessage) const
{
	std::ostream& output =
		eLevel == ELogLevel::Error ? std::cerr : std::clog;

	std::osyncstream synchronizedOutput(output);

	synchronizedOutput
		<< '{'
		<< "\"timestamp\":\""
		<< makeUtcTimestamp()
		<< "\","
		<< "\"severity\":\""
		<< logLevelToString(eLevel)
		<< "\","
		<< "\"service\":\""
		<< escapeJson(m_sServiceName)
		<< "\","
		<< "\"environment\":\""
		<< escapeJson(m_sEnvironment)
		<< "\","
		<< "\"message\":\""
		<< escapeJson(sMessage)
		<< "\""
		<< '}'
		<< '\n';
}

void CLogger::info(std::string_view sMessage) const
{
	log(ELogLevel::Info, sMessage);
}

void CLogger::warning(std::string_view sMessage) const
{
	log(ELogLevel::Warning, sMessage);
}

void CLogger::error(std::string_view sMessage) const
{
	log(ELogLevel::Error, sMessage);
}

}