#ifndef CAPABILITY_MANAGER_HPP
#define CAPABILITY_MANAGER_HPP

#include <string>

class CapabilityManager {
public:
    CapabilityManager();

    std::string getCurrentCapabilities();
    bool dropCapability(const std::string& capabilityName);
};

#endif
