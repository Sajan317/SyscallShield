#include <iostream>

#include "system_info.hpp"
#include "policy_engine.hpp"
#include "seccomp_manager.hpp"
#include "process_manager.hpp"
#include "capability_manager.hpp"
#include "namespace_manager.hpp"
#include "runtime_monitor.hpp"
#include "security_report.hpp"
#include "driver_interface.hpp"

int main()
{

    RuntimeMonitor monitor;
    SecurityReportManager reportManager;
    DriverInterface driverInterface;

    monitor.log(
        EventLevel::INFO,
        "SyscallShield starting");

    // Collect system information
    SystemInfo system = collectSystemInfo();

    // Initialize policy engine
    PolicyEngine engine;

    SecurityPolicy policy =
        engine.getDefaultPolicy();

    // Load policy from external configuration
    if (engine.loadPolicyFromFile(
            "../config/default_policy.conf",
            policy))
    {

        monitor.log(
            EventLevel::INFO,
            "Security policy loaded from configuration");
    }
    else
    {

        monitor.log(
            EventLevel::WARNING,
            "Configuration unavailable, using built-in default policy");
    }

    // Initialize security components
    SeccompManager seccompManager;
    CapabilityManager capabilityManager;
    NamespaceManager namespaceManager;
    ProcessManager processManager;

    // Check Linux device driver
    bool driverAvailable =
        driverInterface.isDriverAvailable();

    std::cout << "========================================\n";
    std::cout << "           SYSCALLSHIELD v0.1\n";
    std::cout << "     Adaptive Linux Runtime Security\n";
    std::cout << "========================================\n\n";

    // System information
    std::cout << "[ SYSTEM ]\n";

    std::cout << "OS              : "
              << system.operatingSystem << '\n';

    std::cout << "Architecture    : "
              << system.architecture << '\n';

    std::cout << "Kernel          : "
              << system.kernelVersion << '\n';

    // Policy information
    std::cout << "\n[ POLICY ENGINE ]\n";

    std::cout << "Policy Name     : "
              << policy.name << '\n';

    std::cout << "Allowed Syscalls: "
              << policy.allowedSyscalls.size() << '\n';

    std::cout << "Restricted      : "
              << policy.restrictedSyscalls.size() << '\n';

    std::cout << "\nAllowed Syscalls:\n";

    for (const auto &syscall : policy.allowedSyscalls)
    {
        std::cout << "  [+] "
                  << syscall
                  << '\n';
    }

    std::cout << "\nRestricted Syscalls:\n";

    for (const auto &syscall : policy.restrictedSyscalls)
    {
        std::cout << "  [-] "
                  << syscall
                  << '\n';
    }

    // Engine status
    std::cout << "\n[ ENGINE STATUS ]\n";

    std::cout << "Policy Engine   : READY\n";
    std::cout << "Runtime Monitor : READY\n";

    std::cout << "Driver Interface: "
              << (driverAvailable
                      ? "AVAILABLE"
                      : "NOT LOADED")
              << '\n';

    std::cout << "Seccomp Module  : READY\n";
    std::cout << "Capability Mgr  : READY\n";
    std::cout << "Namespace Mgr   : READY\n";
    std::cout << "Security Report : READY\n";

    // Driver status
    if (driverAvailable)
    {

        monitor.log(
            EventLevel::SECURITY,
            "SyscallShield driver detected");
    }
    else
    {

        monitor.log(
            EventLevel::WARNING,
            "SyscallShield driver not loaded");
    }

    monitor.log(
        EventLevel::INFO,
        "Security modules initialized");

    // Protected process
    std::cout << "\n[ PROTECTED PROCESS ]\n";

    monitor.log(
        EventLevel::INFO,
        "Starting protected process");

    bool processResult =
        processManager.runProtectedProcess(
            seccompManager,
            capabilityManager,
            namespaceManager);

    if (processResult)
    {

        monitor.log(
            EventLevel::SECURITY,
            "Protected process completed successfully");
    }
    else
    {

        monitor.log(
            EventLevel::ERROR,
            "Protected process failed");
    }

    // Determine namespace status
    bool namespaceAvailable =
        namespaceManager.getStatus() == "ACTIVE";

    // Generate security report
    SecurityReport report{
        true,
        true,
        namespaceAvailable,
        processResult};

    reportManager.setReport(report);

    // Report namespace limitation
    if (!namespaceAvailable)
    {

        monitor.log(
            EventLevel::WARNING,
            "PID namespace unavailable in current environment");
    }

    // Print final security report
    reportManager.printReport();

    monitor.log(
        EventLevel::INFO,
        "SyscallShield execution completed");

    std::cout << "\nStatus          : INITIALIZED\n";

    std::cout << "========================================\n";

    return 0;
}