#include "capability_manager.hpp"

#include <iostream>

#include <sys/capability.h>

CapabilityManager::CapabilityManager() {
}

std::string CapabilityManager::getCurrentCapabilities() {

    cap_t capabilities = cap_get_proc();

    if (capabilities == nullptr) {
        return "Unable to read capabilities";
    }

    char* text = cap_to_text(capabilities, nullptr);

    if (text == nullptr) {
        cap_free(capabilities);
        return "Unable to convert capabilities";
    }

    std::string result(text);

    cap_free(text);
    cap_free(capabilities);

    return result;
}

bool CapabilityManager::dropCapability(
    const std::string& capabilityName) {

    cap_value_t capability;

    if (cap_from_name(capabilityName.c_str(), &capability) != 0) {
        return false;
    }

    cap_t capabilities = cap_get_proc();

    if (capabilities == nullptr) {
        return false;
    }

    if (cap_set_flag(
            capabilities,
            CAP_EFFECTIVE,
            1,
            &capability,
            CAP_CLEAR) != 0) {

        cap_free(capabilities);
        return false;
    }

    if (cap_set_flag(
            capabilities,
            CAP_PERMITTED,
            1,
            &capability,
            CAP_CLEAR) != 0) {

        cap_free(capabilities);
        return false;
    }

    int result = cap_set_proc(capabilities);

    cap_free(capabilities);

    return result == 0;
}
