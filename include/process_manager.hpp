#ifndef PROCESS_MANAGER_HPP
#define PROCESS_MANAGER_HPP

#include <sys/types.h>

#include "seccomp_manager.hpp"
#include "capability_manager.hpp"
#include "namespace_manager.hpp"

class ProcessManager {
public:
    ProcessManager();

    bool runProtectedProcess(
        SeccompManager& seccompManager,
        CapabilityManager& capabilityManager,
        NamespaceManager& namespaceManager
    );
};

#endif
