#include <fortrend/core/error.h>

namespace fortrend::core
{

std::string_view errorCodeToString(EErrorCode eCode) noexcept
{
    switch (eCode) 
    {
        case EErrorCode::InvalidConfiguration:
            return "invalid_configuration";

        case EErrorCode::InternalError:
            return "internal_error";
    }

    return "unknown_error";
}

int errorCodeToExitCode(EErrorCode eCode) noexcept
{
    switch (eCode) 
    {
		case EErrorCode::InvalidConfiguration:
			return 2;

		case EErrorCode::InternalError:
			return 1;        
    }

    return 1;
}

}

