#ifndef RUNTIME_MONITOR_HPP
#define RUNTIME_MONITOR_HPP

#include <fstream>
#include <string>

enum class EventLevel {
    INFO,
    WARNING,
    SECURITY,
    ERROR
};

class RuntimeMonitor {
public:
    RuntimeMonitor();
    ~RuntimeMonitor();

    void log(EventLevel level, const std::string& message);

private:
    std::string levelToString(EventLevel level) const;

    std::ofstream logFile;
};

#endif
