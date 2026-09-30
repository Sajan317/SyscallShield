#ifndef SYSTEM_INFO_HPP
#define SYSTEM_INFO_HPP

#include <string>

struct SystemInfo
{
    std::string operatingSystem;
    std::string architecture;
    std::string kernelVersion;
};

SystemInfo collectSystemInfo();

#endif