#ifndef DRIVER_INTERFACE_HPP
#define DRIVER_INTERFACE_HPP

#include <string>

class DriverInterface {
public:
    DriverInterface();

    bool isDriverAvailable() const;
    std::string getDevicePath() const;
};

#endif
