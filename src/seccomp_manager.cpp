#include "seccomp_manager.hpp"

#include <cerrno>
#include <iostream>

#include <seccomp.h>

SeccompManager::SeccompManager() {
}

bool SeccompManager::blockSyscall(const std::string& syscallName) {

    scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_ALLOW);

    if (ctx == nullptr) {
        return false;
    }

    int syscallNumber =
        seccomp_syscall_resolve_name(syscallName.c_str());

    if (syscallNumber == __NR_SCMP_ERROR) {
        seccomp_release(ctx);
        return false;
    }

    int result = seccomp_rule_add(
        ctx,
        SCMP_ACT_ERRNO(EPERM),
        syscallNumber,
        0
    );

    if (result < 0) {
        seccomp_release(ctx);
        return false;
    }

    result = seccomp_load(ctx);

    seccomp_release(ctx);

    return result == 0;
}

bool SeccompManager::applyDefaultPolicy() {

    std::cout << "\n[ SECCOMP ]\n";

    if (!blockSyscall("ptrace")) {
        std::cout << "Failed to configure ptrace restriction\n";
        return false;
    }

    std::cout << "ptrace restriction configured\n";

    return true;
}
