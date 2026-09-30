#include "system_info.hpp"

#include <sys/utsname.h>

SystemInfo collectSystemInfo()
{

    SystemInfo info;

    struct utsname systemData;

    if (uname(&systemData) == 0)
    {
        info.operatingSystem = systemData.sysname;
        info.architecture = systemData.machine;
        info.kernelVersion = systemData.release;
    }
    else
    {
        info.operatingSystem = "Unknown";
        info.architecture = "Unknown";
        info.kernelVersion = "Unknown";
    }

    return info;
}