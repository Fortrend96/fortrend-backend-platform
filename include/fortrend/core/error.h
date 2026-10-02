#pragma once

#include <string>
#include <string_view>

namespace fortrend::core
{
enum class EErrorCode
{
    InvalidConfiguration,
    InternalError
};

struct SError
{
    EErrorCode m_eCode {EErrorCode::InternalError};
    std::string m_sMessage;
};

std::string_view errorCodeToString(EErrorCode eCode) noexcept;

int errorCodeToExitCode(EErrorCode eCode) noexcept;

}