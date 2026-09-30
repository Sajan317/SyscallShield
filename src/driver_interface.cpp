#include "driver_interface.hpp"

#include <filesystem>

DriverInterface::DriverInterface() {
}

bool DriverInterface::isDriverAvailable() const {

    return std::filesystem::exists(
        getDevicePath()
    );
}

std::string DriverInterface::getDevicePath() const {

    return "/dev/syscallshield";
}
