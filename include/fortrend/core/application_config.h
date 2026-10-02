#pragma once

#include <fortrend/core/error.h>

#include <expected>
#include <string>

namespace fortrend::core
{

struct SApplicationConfig
{
	std::string m_sServiceName{ "fortrend-backend" };
	std::string m_sEnvironment{ "local" };
};

std::expected<SApplicationConfig, SError> loadApplicationConfig();

}