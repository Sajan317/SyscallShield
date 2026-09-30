#ifndef SECURITY_REPORT_HPP
#define SECURITY_REPORT_HPP

#include <string>

struct SecurityReport {
    bool seccompActive;
    bool capabilityReduced;
    bool namespaceAvailable;
    bool protectedProcessCompleted;
};

class SecurityReportManager {
public:
    SecurityReportManager();

    void setReport(const SecurityReport& report);
    void printReport() const;

private:
    SecurityReport report;
};

#endif
