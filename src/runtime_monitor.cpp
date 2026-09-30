#include "runtime_monitor.hpp"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

RuntimeMonitor::RuntimeMonitor()
    : logFile("../logs/syscallshield.log", std::ios::app) {
}

RuntimeMonitor::~RuntimeMonitor() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

std::string RuntimeMonitor::levelToString(
    EventLevel level) const {

    switch (level) {

        case EventLevel::INFO:
            return "INFO";

        case EventLevel::WARNING:
            return "WARNING";

        case EventLevel::SECURITY:
            return "SECURITY";

        case EventLevel::ERROR:
            return "ERROR";
    }

    return "UNKNOWN";
}

void RuntimeMonitor::log(
    EventLevel level,
    const std::string& message) {

    auto now = std::chrono::system_clock::now();

    std::time_t currentTime =
        std::chrono::system_clock::to_time_t(now);

    std::tm localTime{};

    localtime_r(&currentTime, &localTime);

    std::ostringstream timestamp;

    timestamp
        << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");

    std::string entry =
        "[" + timestamp.str() + "] [" +
        levelToString(level) + "] " +
        message;

    std::cout << entry << '\n';

    if (logFile.is_open()) {
        logFile << entry << '\n';
        logFile.flush();
    }
}
