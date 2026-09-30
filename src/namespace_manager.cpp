#include "namespace_manager.hpp"

#include <iostream>

#include <sched.h>

NamespaceManager::NamespaceManager()
    : status("NOT TESTED") {
}

bool NamespaceManager::createPIDNamespace() {

    int result = unshare(CLONE_NEWPID);

    if (result != 0) {

        status = "UNAVAILABLE";

        std::cerr
            << "[NAMESPACE] PID namespace unavailable "
            << "in current environment\n";

        return false;
    }

    status = "ACTIVE";

    std::cout
        << "[NAMESPACE] PID namespace created successfully\n";

    return true;
}

std::string NamespaceManager::getStatus() const {
    return status;
}
