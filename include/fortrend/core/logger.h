#pragma once

#include <string>
#include <string_view>

namespace fortrend::core
{

enum class ELogLevel
{
    Info,
    Warning,
    Error
};

class CLogger final
{
public:
    CLogger(std::string sServiceName, std::string sEnvironment);

    void log(ELogLevel eLevel, std::string_view sMessage) const;

    void info(std::string_view sMessage) const;
    void warning(std::string_view sMessage) const; 
    void error(std::string_view sMessage) const;

private:
    std::string m_sServiceName;
    std::string m_sEnvironment;
};
}


