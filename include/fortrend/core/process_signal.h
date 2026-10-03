#pragma once

#include <fortrend/core/error.h>

#include <expected>
#include <string_view>

namespace fortrend::core
{
[[nodiscard]] std::expected<void, SError> installShutdownSignalHandlers();

[[nodiscard]] bool isShutdownRequested() noexcept;

[[nodiscard]] int shutdownSignal() noexcept;

[[nodiscard]] std::string_view signalToString(int nSignal) noexcept;

}