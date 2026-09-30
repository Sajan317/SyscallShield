#include "process_manager.hpp"

#include <cerrno>
#include <cstring>
#include <iostream>

#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>

ProcessManager::ProcessManager() {
}

bool ProcessManager::runProtectedProcess(
    SeccompManager& seccompManager,
    CapabilityManager& capabilityManager,
    NamespaceManager& namespaceManager) {

    pid_t pid = fork();

    if (pid < 0) {
        std::cerr << "[PROCESS] Failed to create child process\n";
        return false;
    }

    if (pid == 0) {

        std::cerr << "[PROCESS] Protected child started\n";

        // Capability reduction
        std::string capabilities =
            capabilityManager.getCurrentCapabilities();

        std::cerr << "[CAPABILITY] Before reduction:\n";
        std::cerr << capabilities << '\n';

        if (capabilityManager.dropCapability("CAP_NET_RAW")) {
            std::cerr << "[CAPABILITY] CAP_NET_RAW dropped\n";
        } else {
            std::cerr << "[CAPABILITY] CAP_NET_RAW could not be dropped "
                         "or was not available\n";
        }

        std::string updatedCapabilities =
            capabilityManager.getCurrentCapabilities();

        std::cerr << "[CAPABILITY] After reduction:\n";
        std::cerr << updatedCapabilities << '\n';

        // Namespace test
        bool namespaceCreated =
            namespaceManager.createPIDNamespace();

        // Seccomp
        if (!seccompManager.applyDefaultPolicy()) {
            std::cerr << "[SECCOMP] Failed to apply policy\n";
            _exit(1);
        }

        std::cerr << "[SECCOMP] Policy applied successfully\n";

        // Security test
        errno = 0;

        long result =
            ptrace(PTRACE_TRACEME, 0, nullptr, nullptr);

        if (result == -1) {

            std::cerr << "[SECURITY TEST] ptrace blocked\n";

            std::cerr << "[SECURITY TEST] errno: "
                      << errno << " ("
                      << std::strerror(errno) << ")\n";

        } else {

            std::cerr << "[SECURITY TEST] ptrace was allowed\n";
        }

        std::cerr.flush();

        /*
         * Exit codes:
         * 0 = all required security tests completed
         * 2 = PID namespace unavailable
         */
        if (!namespaceCreated) {
            _exit(2);
        }

        _exit(0);
    }

    std::cout << "[PROCESS] Protected child PID: "
              << pid << '\n';

    int status = 0;

    if (waitpid(pid, &status, 0) < 0) {
        std::cerr << "[PROCESS] Failed waiting for child\n";
        return false;
    }

    if (WIFEXITED(status)) {

        int exitStatus = WEXITSTATUS(status);

        std::cout << "[PROCESS] Protected child exited with status: "
                  << exitStatus << '\n';

        if (exitStatus == 2) {
            std::cout
                << "[PROCESS] Namespace unavailable reported by child\n";
        }

        return exitStatus == 0 || exitStatus == 2;
    }

    return false;
}
