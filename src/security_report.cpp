#include "security_report.hpp"

#include <iostream>

SecurityReportManager::SecurityReportManager()
    : report{
          false,
          false,
          false,
          false
      } {
}

void SecurityReportManager::setReport(
    const SecurityReport& newReport) {

    report = newReport;
}

void SecurityReportManager::printReport() const {

    std::cout << "\n========================================\n";
    std::cout << "        SYSCALLSHIELD SECURITY REPORT\n";
    std::cout << "========================================\n";

    std::cout << "Seccomp             : "
              << (report.seccompActive ? "ACTIVE" : "INACTIVE")
              << '\n';

    std::cout << "Capability Reduction: "
              << (report.capabilityReduced ? "ACTIVE" : "INACTIVE")
              << '\n';

    std::cout << "PID Namespace       : "
              << (report.namespaceAvailable ? "AVAILABLE" : "UNAVAILABLE")
              << '\n';

    std::cout << "Protected Process   : "
              << (report.protectedProcessCompleted
                      ? "COMPLETED"
                      : "FAILED")
              << '\n';

    std::cout << "========================================\n";
}
